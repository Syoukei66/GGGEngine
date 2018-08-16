#include "RenderTexture.h"
#include "NativeProcess.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcRenderTexture* rcRenderTexture::Create(T_UINT16 width, T_UINT16 height, rcRenderBuffer::Format format)
{
  return NativeProcess::Resource::CreateRenderTexture(width, height, format, rcRenderBuffer::FORMAT_D16);
}

rcRenderTexture* rcRenderTexture::Create(T_UINT16 width, T_UINT16 height, rcRenderBuffer::Format format, rcRenderBuffer::Format depth_format)
{
  return NativeProcess::Resource::CreateRenderTexture(width, height, format, depth_format);
}

rcRenderTexture* rcRenderTexture::Create(T_UINT16 width, T_UINT16 height, void* native_obj, rcRenderBuffer::Format depth_format)
{
  rcRenderTexture* ret = new rcRenderTexture(width, height, native_obj, depth_format);
  ret->Resource::Init();
  return ret;
}

rcRenderTexture::rcRenderTexture(T_UINT16 width, T_UINT16 height, void* native_obj, rcRenderBuffer::Format depth_format)
  : rcTexture(width, height, native_obj)
{
  this->depth_stencil_buffer_ = rcRenderBuffer::CreateDepthStencilBuffer(this->GetTwoPoweredWidth(), this->GetTwoPoweredHeight(), depth_format);
}

rcRenderTexture::~rcRenderTexture()
{
  this->depth_stencil_buffer_->Release();
}

// =================================================================
// Methods
// =================================================================
void rcRenderTexture::RenderBegin(bool clear)
{
  NativeProcess::Graphics::SetRenderTarget(this->GetColorBuffer(), this->depth_stencil_buffer_, clear);
}

void rcRenderTexture::RenderEnd()
{
  NativeProcess::Graphics::ResetRenderTarget();
}
