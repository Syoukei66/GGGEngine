#include "DX11TextureResource.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

UniqueRef<rcTextureResource> rcTextureResource::Create(const TextureResourceData& data)
{
  return UniqueRef<rcTextureResource>(new DX11TextureResource(data));
}

// =================================================================
// Constructor / Destructor
// =================================================================
DX11TextureResource::DX11TextureResource(const TextureResourceData& data)
{
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();

  this->format_ = static_cast<DXGI_FORMAT>(data.format_);

  // テクスチャリソースの作成
  D3D11_TEXTURE2D_DESC texture_desc = D3D11_TEXTURE2D_DESC();
  texture_desc.Width = data.width_;
  texture_desc.Height = data.height_;
  texture_desc.MipLevels = data.mip_map_levels_;
  texture_desc.ArraySize = 1;
  texture_desc.Format = this->format_;
  texture_desc.SampleDesc.Count = 1;
  texture_desc.SampleDesc.Quality = 0;
  texture_desc.Usage = D3D11_USAGE_IMMUTABLE;
  texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  texture_desc.CPUAccessFlags = 0;
  texture_desc.MiscFlags = 0;

  std::vector<D3D11_SUBRESOURCE_DATA> initial_datas = std::vector<D3D11_SUBRESOURCE_DATA>(data.mip_map_levels_);
  T_UINT64 offset = 0;
  T_UINT32 width = data.width_;
  T_UINT32 height = data.height_;
  for (T_UINT8 i = 0; i < data.mip_map_levels_; ++i)
  {
    D3D11_SUBRESOURCE_DATA initial_data = D3D11_SUBRESOURCE_DATA();
    initial_data.pSysMem = &data.data_[offset];
    initial_data.SysMemPitch = (width * data.block_size_ * data.bits_per_pixel_) / 8;
    initial_data.SysMemSlicePitch = 0;
    initial_datas[i] = initial_data;
    offset += (width * height * data.bits_per_pixel_) / 8;
    width = width >> 1;
    height = height >> 1;
  }

  HRESULT hr = device->CreateTexture2D(&texture_desc, &initial_datas[0], &this->resource_);
  GG_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");
}

DX11TextureResource::~DX11TextureResource()
{
  this->resource_->Release();
}


#endif
