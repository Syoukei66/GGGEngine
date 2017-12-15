#pragma once

#include <string>
#include "NativeType.h"
#include "Geometry.h"

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
  virtual const LP_TEXTURE GetNativeTexture() const = 0;
  virtual const TSize& GetSize() const = 0;
};