#pragma once

#include "NativeTexture.h"

class INativeRenderTexture : public INativeTexture
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  enum Format
  {
    TEXTURE_FORMAT_R8G8B8A8,
    TEXTURE_FORMAT_R16G16B16A16,
    TEXTURE_FORMAT_R16G16B16A16F,

    TEXTURE_FORMAT_DATANUM,
  };

  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeRenderTexture* Create(T_UINT16 width, T_UINT16 height, Format format = TEXTURE_FORMAT_R8G8B8A8);

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
