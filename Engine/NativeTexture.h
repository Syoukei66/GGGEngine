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

protected:
  static T_UINT16 CalcTwoPowerValue(T_UINT16 val);

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
  virtual T_UINT16 GetTwoPoweredWidth() const = 0;
  virtual T_UINT16 GetTwoPoweredHeight() const = 0;
};