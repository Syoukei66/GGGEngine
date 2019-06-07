#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/TextureView.h>

class DX11TextureView : public rcTextureView
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11TextureView(const TextureViewData& data, const SharedRef<rcTextureResource>& resource);
  ~DX11TextureView();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void SetToHardware(T_UINT8 index) const override;
  virtual ImTextureID GetImTextureID() const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3D11ShaderResourceView* resource_view_;
  ID3D11SamplerState* sampler_state_;

};

#endif
