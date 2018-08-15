#pragma once

#include "../Core/Texture.h"
#include "../Core/RenderBuffer.h"
#include "../Core/GraphicsConstants.h"

class RenderTexture : public Texture
{
public:
  static RenderTexture* Create(T_UINT16 width, T_UINT16 height, RenderBuffer::Format format);
  static RenderTexture* Create(T_UINT16 width, T_UINT16 height, RenderBuffer::Format format, RenderBuffer::Format depth_format);

protected:
  RenderTexture(T_UINT16 width, T_UINT16 height, RenderBuffer::Format format, RenderBuffer::Format depth_format);

public:
  virtual ~RenderTexture();

public:
  void RenderBegin(bool clear = false);
  void RenderEnd();

private:
  RenderBuffer* depth_buffer_;

};