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
  DX11TextureResource(ID3D11ShaderResourceView* resource_view);
  ~DX11TextureResource();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void SetResource(T_UINT32 index) const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3D11ShaderResourceView* resource_view_;
  ID3D11SamplerState* sampler_state_;

};

#endif
