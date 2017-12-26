#pragma once

#include <string>
#include "Geometry.h"
#include "NativeTexture.h"

class ITexture
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ~ITexture() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual bool IsLoaded() const = 0;
  virtual const INativeTexture* GetNativeTexture() const = 0;
  virtual T_UINT16 GetWidth() const = 0;
  virtual T_UINT16 GetHeight() const = 0;
};