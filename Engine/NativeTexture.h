#pragma once

#include "NativeObject.h"
#include "Geometry.h"

typedef struct NativeTextureInstance {};

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
    : NativeObject(instance)
  {}
  virtual ~INativeTexture() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual T_FLOAT GetWidth() const = 0;
  virtual T_FLOAT GetHeight() const = 0;

};