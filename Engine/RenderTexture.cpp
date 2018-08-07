#include "RenderTexture.h"
#include "../Common/NativeProcess.h"

RenderTexture* RenderTexture::Create(T_UINT16 width, T_UINT16 height, Graphics::TextureFormat format)
{
  return new RenderTexture(width, height, format, Graphics::TEX_FORMAT_D16);
}

RenderTexture * RenderTexture::Create(T_UINT16 width, T_UINT16 height, Graphics::TextureFormat format, Graphics::TextureFormat depth_format)
{
  return new RenderTexture(width, height, format, depth_format);
}

RenderTexture::RenderTexture(T_UINT16 width, T_UINT16 height, Graphics::TextureFormat format, Graphics::TextureFormat depth_format)
  : Texture(width, height, NativeProcess::Resource::CreateTexture(width, height, format))
{
  this->depth_buffer_ = RenderBuffer::CreateDepthBuffer(this->GetTwoPoweredWidth(), this->GetTwoPoweredHeight(), depth_format);
}

RenderTexture::~RenderTexture()
{
  delete this->depth_buffer_;
}

void RenderTexture::RenderBegin(bool clear)
{
  NativeProcess::Graphics::SetRenderTarget(this->GetColorBuffer(), this->depth_buffer_, clear);
}

void RenderTexture::RenderEnd()
{
  NativeProcess::Graphics::ResetRenderTarget();
}
