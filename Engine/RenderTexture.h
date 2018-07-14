#pragma once

#include "Texture.h"
#include "RenderBuffer.h"
#include "GraphicsConstants.h"

class RenderTexture : public Texture
{
public:
  static RenderTexture* Create(T_UINT16 width, T_UINT16 height, Graphics::TextureFormat format);
  static RenderTexture* Create(T_UINT16 width, T_UINT16 height, Graphics::TextureFormat format, Graphics::TextureFormat depth_format);

protected:
  RenderTexture(T_UINT16 width, T_UINT16 height, Graphics::TextureFormat format, Graphics::TextureFormat depth_format);

public:
  virtual ~RenderTexture();

public:
  inline RenderBuffer* GetDepthBuffer()
  {
    return this->depth_buffer_;
  }
  inline const RenderBuffer* GetDepthBuffer() const
  {
    return this->depth_buffer_;
  }

private:
  RenderBuffer* depth_buffer_;

};