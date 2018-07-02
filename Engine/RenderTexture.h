#pragma once

#include "Texture.h"
#include "RenderBuffer.h"
#include "GraphicsConstants.h"

class RenderTexture : public Texture
{
public:
  static RenderTexture* Create(T_UINT16 width, T_UINT16 height, GraphicsConstants::TextureFormat format);

protected:
  RenderTexture(T_UINT16 width, T_UINT16 height, GraphicsConstants::TextureFormat format);

public:
  virtual ~RenderTexture();

public:
  void RenderBegin(bool clear = false);
  void RenderEnd();

private:
  RenderBuffer* depth_buffer_;

};