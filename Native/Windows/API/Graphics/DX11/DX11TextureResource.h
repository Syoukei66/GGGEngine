#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/TextureResource.h>

class DX11TextureResource : public rcTextureResource
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11TextureResource(const TextureResourceData& data);
  ~DX11TextureResource();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void SetResource(T_UINT8 index) const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3D11Texture2D* resource_;
  ID3D11ShaderResourceView* resource_view_;
  ID3D11SamplerState* sampler_state_;

};

UniqueRef<rcTextureResource> rcTextureResource::Create(const TextureResourceData& data)
{
  return UniqueRef<rcTextureResource>(new DX11TextureResource(data));
}

#endif
