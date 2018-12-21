#include "DX11TextureView.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

#include "DX11TextureResource.h"

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

  // �e�N�X�`�����\�[�X�r���[�̍쐬
  D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc = D3D11_SHADER_RESOURCE_VIEW_DESC();
  resource_view_desc.Format = dx11_resource->GetFormat();
  resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  resource_view_desc.Texture2D.MipLevels = 1;
  resource_view_desc.Texture2D.MostDetailedMip = 0;

  HRESULT hr = device->CreateShaderResourceView(dx11_resource->GetResource(), &resource_view_desc, &this->resource_view_);

  // �T���v���[�̍쐬
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
  GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���T���v���[�̍쐬�Ɏ��s���܂���");
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