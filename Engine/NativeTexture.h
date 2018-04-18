#pragma once

#include "NativeType.h"
#include "NativeObject.h"

struct NativeTextureInstance { void* p; };

class INativeTexture : public NativeObject<NativeTextureInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeTexture* Create(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeTexture(NativeTextureInstance* instance)
    : NativeObject<NativeTextureInstance>(instance)
  {}
  virtual ~INativeTexture() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual T_UINT16 GetWidth() const = 0;
  virtual T_UINT16 GetHeight() const = 0;
};