#pragma once

#include "GraphicsConstants.h"

class Texture;

class RenderBuffer
{
public:
  enum Format
  {
    FORMAT_D16,
    FORMAT_D24S8,
    FORMAT_D32,
    FORMAT_R8G8B8A8,
    FORMAT_R16G16B16A16,
    FORMAT_R16G16B16A16F,

    FORMAT_DATANUM,
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  static RenderBuffer* CreateColorBuffer(Texture* texture);
  static RenderBuffer* CreateDepthBuffer(T_UINT16 width, T_UINT16 height, Format format);

private:
  RenderBuffer(void* native_obj);

public:
  ~RenderBuffer();

  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline void* GetNativeObject()
  {
    return this->native_obj_;
  }

  inline const void* GetNativeObject() const
  {
    return this->native_obj_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  void* native_obj_;

};