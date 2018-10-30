#include "RenderBuffer.h"
#include <Core/Native/NativeProcess.h>

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcRenderBuffer> rcRenderBuffer::CreateColorBuffer(const SharedRef<const rcTexture>&  texture)
{
  return NativeProcess::Resource::CreateColorBuffer(texture);
}

UniqueRef<rcRenderBuffer> rcRenderBuffer::CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, Graphics::PixelFormat format)
{
  return NativeProcess::Resource::CreateDepthStencilBuffer(width, height, format);
}

UniqueRef<rcRenderBuffer> rcRenderBuffer::Create(void* native_obj)
{
  return UniqueRef<rcRenderBuffer>(new rcRenderBuffer(native_obj));
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcRenderBuffer::rcRenderBuffer(void* native_obj)
  : native_obj_(native_obj)
{
}

rcRenderBuffer::~rcRenderBuffer()
{
  NativeProcess::Resource::DeleteRenderBuffer(this);
}