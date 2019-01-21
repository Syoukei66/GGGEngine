#include "DX11TextureView.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

#include "DX11TextureResource.h"
#include "DX11Constants.h"

UniqueRef<rcTextureView> rcTextureView::Create(const TextureViewData& data, const SharedRef<rcTextureResource>& resource)
{
  return UniqueRef<rcTextureView>(new DX11TextureView(data, resource));
}

// =================================================================
// Constructor / Destructor
// =================================================================
DX11TextureView::DX11TextureView(const TextureViewData& data, const SharedRef<rcTextureResource>& resource)
{
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();

  const SharedRef<DX11TextureResource>& dx11_resource = SharedRef<DX11TextureResource>::StaticCast(resource);

  // テクスチャリソースビューの作成
  D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc = D3D11_SHADER_RESOURCE_VIEW_DESC();
  resource_view_desc.Format = dx11_resource->GetFormat();
  resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  resource_view_desc.Texture2D.MipLevels = -1;
  resource_view_desc.Texture2D.MostDetailedMip = 0;

  HRESULT hr = device->CreateShaderResourceView(dx11_resource->GetResource(), &resource_view_desc, &this->resource_view_);

  using namespace DX11;
  // サンプラーの作成
  D3D11_SAMPLER_DESC sampDesc = D3D11_SAMPLER_DESC();
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  if (data.aniso_level_ == 1)
  {
    sampDesc.Filter = TEXTURE_FILTERS[data.filter_];
  }
  else
  {
    sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
    sampDesc.MaxAnisotropy = data.aniso_level_;
  }
  sampDesc.AddressU = TEXTURE_ADDRESS_MODES[data.address_u_];
  sampDesc.AddressV = TEXTURE_ADDRESS_MODES[data.address_v_];
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  //if (data.fade_start_ == 0.0f && data.fade_end_ == 0.0f)
  {
    sampDesc.MinLOD = 0.0f;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
  }
  //else
  //{
  //  sampDesc.MinLOD = data.fade_start_;
  //  sampDesc.MaxLOD = data.fade_end_;
  //}

  hr = device->CreateSamplerState(&sampDesc, &this->sampler_state_);
  GG_ASSERT(SUCCEEDED(hr), "テクスチャサンプラーの作成に失敗しました");
}

DX11TextureView::~DX11TextureView()
{
  this->sampler_state_->Release();
  this->resource_view_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11TextureView::SetToHardware(T_UINT8 index) const
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->VSSetShaderResources(index, 1, &this->resource_view_);
  context->VSSetSamplers(index, 1, &this->sampler_state_);
  context->PSSetShaderResources(index, 1, &this->resource_view_);
  context->PSSetSamplers(index, 1, &this->sampler_state_);
}

#endif