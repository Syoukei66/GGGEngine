#pragma once

#include "../../Engine/NativeTexture.h"

#include <d3d9.h>
#include <d3dx9.h>

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
  virtual T_FLOAT GetWidth() const override;
  virtual T_FLOAT GetHeight() const override;

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
private:
  D3DSURFACE_DESC desc_;
};