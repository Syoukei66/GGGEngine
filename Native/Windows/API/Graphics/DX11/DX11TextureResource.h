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
  DX11TextureResource(const TextureResourceData& data, Usage usage);
  ~DX11TextureResource();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) override;
  virtual void Unlock() override;

  // =================================================================
  // Data Members
  // =================================================================
public:
  DXGI_FORMAT GetFormat() const
  {
    return this->format_;
  }

  ID3D11Texture2D* GetResource() const
  {
    return this->resource_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3D11Texture2D* resource_;
  DXGI_FORMAT format_;

};

#endif
