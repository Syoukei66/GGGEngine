#pragma once

#include "NativeTexture.h"

class INativeRenderTexture : public INativeTexture
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeRenderTexture* Create(T_UINT16 width, T_UINT16 height);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeRenderTexture(NativeTextureInstance* instance)
    : INativeTexture(instance)
  {}
  virtual ~INativeRenderTexture() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void RenderBegin(bool clear = false) = 0;
  virtual void RenderEnd() = 0;

};
