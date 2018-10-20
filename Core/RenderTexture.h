#pragma once

#include "Texture.h"
#include "RenderBuffer.h"
#include "GraphicsConstants.h"

class rcRenderTexture : public rcTexture
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcRenderTexture> Create(T_UINT16 width, T_UINT16 height, rcRenderBuffer::Format format);
  static UniqueResource<rcRenderTexture> Create(T_UINT16 width, T_UINT16 height, rcRenderBuffer::Format format, rcRenderBuffer::Format depth_format);
  static UniqueResource<rcRenderTexture> Create(T_UINT16 width, T_UINT16 height, void* native_obj, rcRenderBuffer::Format depth_format);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcRenderTexture(T_UINT16 width, T_UINT16 height, void* native_obj, rcRenderBuffer::Format depth_format);
  virtual ~rcRenderTexture();

  // =================================================================
  // Method
  // =================================================================
public:
  void RenderBegin(bool clear = false);
  void RenderEnd();

  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "RenderTexture";
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<rcRenderBuffer> depth_stencil_buffer_;

};