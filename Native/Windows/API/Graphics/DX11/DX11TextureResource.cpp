#include "DX11TextureResource.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

// =================================================================
// Constructor / Destructor
// =================================================================
DX11TextureResource::DX11TextureResource(const TextureResourceData& data)
{
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();

  // テクスチャリソースの作成
  D3D11_TEXTURE2D_DESC texture_desc = D3D11_TEXTURE2D_DESC();
  texture_desc.Width = data.width_;
  texture_desc.Height = data.height_;
  texture_desc.MipLevels = 1;
  texture_desc.ArraySize = 1;
  texture_desc.Format = static_cast<DXGI_FORMAT>(data.format_);
  texture_desc.SampleDesc.Count = 1;
  texture_desc.SampleDesc.Quality = 0;
  texture_desc.Usage = D3D11_USAGE_IMMUTABLE;
  texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  texture_desc.CPUAccessFlags = 0;
  texture_desc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA initial_data = D3D11_SUBRESOURCE_DATA();
  initial_data.pSysMem = data.data_.data();
  initial_data.SysMemPitch = data.width_ * data.bytes_per_pixel_;
  initial_data.SysMemSlicePitch = 0;

  HRESULT hr = device->CreateTexture2D(&texture_desc, &initial_data, &this->resource_);
  GG_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");

  // テクスチャリソースビューの作成
  D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc = D3D11_SHADER_RESOURCE_VIEW_DESC();
  resource_view_desc.Format = static_cast<DXGI_FORMAT>(data.format_);
  resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  resource_view_desc.Texture2D.MipLevels = 1;
  resource_view_desc.Texture2D.MostDetailedMip = 0;

  hr = device->CreateShaderResourceView(this->resource_, &resource_view_desc, &this->resource_view_);

  // サンプラーの作成
  D3D11_SAMPLER_DESC sampDesc = D3D11_SAMPLER_DESC();
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

  hr = device->CreateSamplerState(&sampDesc, &this->sampler_state_);
  GG_ASSERT(SUCCEEDED(hr), "テクスチャサンプラーの作成に失敗しました");
}

DX11TextureResource::~DX11TextureResource()
{
  this->sampler_state_->Release();
  this->resource_->Release();
  this->resource_view_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11TextureResource::SetResource(T_UINT8 index) const
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->VSSetShaderResources(index, 1, &this->resource_view_);
  context->VSSetSamplers(index, 1, &this->sampler_state_);
  context->PSSetShaderResources(index, 1, &this->resource_view_);
  context->PSSetSamplers(index, 1, &this->sampler_state_);
}

#endif
