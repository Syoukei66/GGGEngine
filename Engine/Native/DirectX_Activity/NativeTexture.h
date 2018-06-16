#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <NativeTexture.h>

class NativeTexture : public INativeTexture
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeTexture(const char* path);
  ~NativeTexture();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual T_UINT16 GetWidth() const override;
  virtual T_UINT16 GetHeight() const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  D3DSURFACE_DESC desc_;
};