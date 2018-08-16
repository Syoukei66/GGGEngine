#include "RenderBuffer.h"
#include "NativeProcess.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcRenderBuffer* rcRenderBuffer::CreateColorBuffer(rcTexture* texture)
{
  return NativeProcess::Resource::CreateColorBuffer(texture);
}

rcRenderBuffer* rcRenderBuffer::CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, Format format)
{
  return NativeProcess::Resource::CreateDepthStencilBuffer(width, height, format);
}

rcRenderBuffer* rcRenderBuffer::Create(void* native_obj)
{
  rcRenderBuffer* ret = new rcRenderBuffer(native_obj);
  ret->Resource::Init();
  return ret;
}

rcRenderBuffer::rcRenderBuffer(void* native_obj)
  : native_obj_(native_obj)
{
}

rcRenderBuffer::~rcRenderBuffer()
{
  NativeProcess::Resource::DeleteRenderBuffer(this);
}