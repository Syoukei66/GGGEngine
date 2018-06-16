#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <NativeRenderTexture.h>

class NativeRenderTexture : public INativeRenderTexture
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeRenderTexture(T_UINT16 width, T_UINT16 height, INativeRenderTexture::Format format);
  ~NativeRenderTexture();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual T_UINT16 GetWidth() const override;
  virtual T_UINT16 GetHeight() const override;

  virtual void RenderBegin(bool clear) override;
  virtual void RenderEnd() override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  D3DSURFACE_DESC desc_;
  LPDIRECT3DTEXTURE9 texture_;
  LPDIRECT3DSURFACE9 texture_surface_;
  LPDIRECT3DSURFACE9 depth_surface_;

  LPDIRECT3DSURFACE9 surface_temp_;
  LPDIRECT3DSURFACE9 depth_surface_temp_;

};
