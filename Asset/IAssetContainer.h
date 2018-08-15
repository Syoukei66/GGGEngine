#pragma once

#include <string>
#include "../Core/NativeType.h"

class IAssetContainer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~IAssetContainer() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Retain() = 0;
  virtual void Release() = 0;

  virtual T_INT16 GetReferenceCount() const = 0;

  virtual T_UINT32 GetSize() const = 0;

};