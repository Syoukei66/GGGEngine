#pragma once

#include "GraphicsConstants.h"

class Texture;

class RenderBuffer
{
public:
  RenderBuffer(T_UINT16 width, T_UINT16 height, GraphicsConstants::TextureFormat format);
  RenderBuffer(Texture* texture);
  ~RenderBuffer();

public:
  inline void* GetNativeObject()
  {
    return this->native_obj_;
  }

  inline const void* GetNativeObject() const
  {
    return this->native_obj_;
  }

private:
  void* native_obj_;

};