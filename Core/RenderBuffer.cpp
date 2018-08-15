#include "RenderBuffer.h"
#include "NativeProcess.h"

RenderBuffer* RenderBuffer::CreateColorBuffer(Texture* texture)
{
  return new RenderBuffer(NativeProcess::Resource::CreateColorBuffer(texture));
}

RenderBuffer* RenderBuffer::CreateDepthBuffer(T_UINT16 width, T_UINT16 height, Format format)
{
  return new RenderBuffer(NativeProcess::Resource::CreateDepthBuffer(width, height, format));
}

RenderBuffer::RenderBuffer(void* native_obj)
  : native_obj_(native_obj)
{
}

RenderBuffer::~RenderBuffer()
{
  NativeProcess::Resource::DeleteRenderBuffer(this->native_obj_);
}