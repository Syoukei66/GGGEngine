#include "DX11TextureResource.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

// =================================================================
// Constructor / Destructor
// =================================================================
DX11TextureResource::DX11TextureResource(ID3D11ShaderResourceView* resource_view)
  : resource_view_(resource_view)
{
  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();

  HRESULT hr = device->CreateSamplerState(&sampDesc, &this->sampler_state_);

  GG_ASSERT(SUCCEEDED(hr), "定数バッファの作成に失敗しました");
}

DX11TextureResource::~DX11TextureResource()
{
  this->resource_view_->Release();
  this->sampler_state_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11TextureResource::SetResource(T_UINT32 index) const
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->VSSetShaderResources(index, 1, &this->resource_view_);
  context->VSSetSamplers(index, 1, &this->sampler_state_);
  context->PSSetShaderResources(index, 1, &this->resource_view_);
  context->PSSetSamplers(index, 1, &this->sampler_state_);
}

#endif
