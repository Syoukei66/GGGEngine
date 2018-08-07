#pragma once

#include "GraphicsConstants.h"

class Texture;

class RenderBuffer
{
public:
  static RenderBuffer* CreateColorBuffer(Texture* texture);
  static RenderBuffer* CreateDepthBuffer(T_UINT16 width, T_UINT16 height, Graphics::TextureFormat format);

private:
  RenderBuffer(void* native_obj);

public:
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