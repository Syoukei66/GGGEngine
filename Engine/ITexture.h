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
  virtual const NativeTexture* GetNativeTexture() const = 0;
  virtual const TSize& GetSize() const = 0;
};