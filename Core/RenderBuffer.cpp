#include "RenderBuffer.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcRenderBuffer> rcRenderBuffer::CreateColorBuffer(const SharedRef<const rcTexture>&  texture)
{
  return NativeProcess::Resource::CreateColorBuffer(texture);
}

UniqueResource<rcRenderBuffer> rcRenderBuffer::CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, Format format)
{
  return NativeProcess::Resource::CreateDepthStencilBuffer(width, height, format);
}

UniqueResource<rcRenderBuffer> rcRenderBuffer::Create(void* native_obj)
{
  rcRenderBuffer* ret = new rcRenderBuffer(native_obj);
  ret->Resource::Init();
  return UniqueResource<rcRenderBuffer>(ret);
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