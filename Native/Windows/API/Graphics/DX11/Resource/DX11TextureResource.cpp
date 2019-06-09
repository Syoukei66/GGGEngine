#include "DX11TextureResource.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/API/Graphics/DX11/DX11Constants.h>
#include <Native/Windows/API/Graphics/DX11/Module/DX11TextureModule.h>
#include <Native/Windows/WindowsApplication.h>
#include <Native/ThirdParty/DirectXTex/WICTextureLoader/WICTextureLoader.h>

#pragma comment(lib, "DirectXTex.lib")

// =================================================================
// GGG Statement
// =================================================================
GG_NATIVE_CREATE_FUNC_IMPL_2(rcTextureResource, DX11TextureResource, const TextureResourceData&, data, Usage, usage);

GG_CREATE_FUNC_IMPL_2(DX11TextureResource, const TextureResourceData&, data, Usage, usage)
{
  ID3D11Device* device = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice();
  const SharedRef<DX11TextureModule>& texture_module = SharedRef<DX11TextureModule>::StaticCast(Application::GetPlatform()->GetGraphicsAPI()->GetTextureModule());

  // テクスチャリソースの作成
  D3D11_TEXTURE2D_DESC texture_desc = D3D11_TEXTURE2D_DESC();
  texture_desc.Width = data.width_;
  texture_desc.Height = data.height_;
  texture_desc.MipLevels = data.mip_map_levels_;
  texture_desc.ArraySize = 1;
  texture_desc.Format = texture_module->GetTextureFormat(data.format_, false);
  texture_desc.SampleDesc.Count = 1;
  texture_desc.SampleDesc.Quality = 0;
  if (usage == Usage::kImmutable)
  {
    texture_desc.Usage = D3D11_USAGE_IMMUTABLE;
    texture_desc.CPUAccessFlags = 0;
  }
  else if (usage == Usage::kUltraDynamic)
  {
    texture_desc.Usage = D3D11_USAGE_DYNAMIC;
    texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  }
  texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  texture_desc.MiscFlags = 0;

  if (data.data_.size() > 0)
  {
    // 最適化されていないデータだったら最適化する
    TextureResourceData buf = TextureResourceData();
    const TextureResourceData* optimized = texture_module->OptimisationResourceData(data, &buf);
    texture_desc.Width = optimized->width_;
    texture_desc.Height = optimized->height_;
    texture_desc.MipLevels = optimized->mip_map_levels_;
    texture_desc.Format = texture_module->GetTextureFormat(optimized->format_, false);

    std::vector<D3D11_SUBRESOURCE_DATA> initial_datas = std::vector<D3D11_SUBRESOURCE_DATA>(optimized->mip_map_levels_);
    T_FIXED_UINT16 width = optimized->width_;
    T_FIXED_UINT16 height = optimized->height_;
    T_UINT64 offset = 0;
    for (T_UINT8 i = 0; i < optimized->mip_map_levels_; ++i)
    {
      D3D11_SUBRESOURCE_DATA initial_data = D3D11_SUBRESOURCE_DATA();
      initial_data.pSysMem = &optimized->data_[offset];
      initial_data.SysMemPitch = (width * optimized->block_size_ * optimized->bits_per_pixel_) / 8;
      initial_data.SysMemSlicePitch = 0;
      initial_datas[i] = initial_data;
      offset += (width * height * optimized->bits_per_pixel_) / 8;
      width = width >> 1;
      height = height >> 1;
    }
    HRESULT hr = device->CreateTexture2D(&texture_desc, &initial_datas[0], &this->resource_);
    GG_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");
  }
  else
  {
    HRESULT hr = device->CreateTexture2D(&texture_desc, nullptr, &this->resource_);
    GG_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");
  }

  this->format_ = texture_desc.Format;
  return true;
}

GG_DESTRUCT_FUNC_IMPL(DX11TextureResource)
{
  this->resource_->Release();
  return true;
}

// =================================================================
// Methods from rcTextureResource
// =================================================================
void DX11TextureResource::UpdateSubresource(const TextureResourceData& data, Usage usage)
{
  ID3D11DeviceContext* context = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetImmediateContext();
  D3D11_MAPPED_SUBRESOURCE mapped_subresource = D3D11_MAPPED_SUBRESOURCE();
  HRESULT hr = context->Map(this->resource_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
  GG_ASSERT(SUCCEEDED(hr), "VertexBufferのロックに失敗しました");

  const SharedRef<TextureModule>& texture_module = Application::GetPlatform()->GetGraphicsAPI()->GetTextureModule();

  TextureResourceData buf = TextureResourceData();
  const TextureResourceData* optimized = texture_module->OptimisationResourceData(data, &buf);
  memcpy(mapped_subresource.pData, optimized->data_.data(), optimized->data_.size());
  context->Unmap(this->resource_, 0);
}

#endif
