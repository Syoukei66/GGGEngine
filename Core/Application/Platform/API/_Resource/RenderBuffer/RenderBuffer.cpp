#include "RenderBuffer.h"

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcRenderBuffer> rcRenderBuffer::CreateColorBuffer(const SharedRef<const rcTexture>&  texture)
{
  return Application::GetPlatform()->GetGraphicsAPI()->CreateColorBuffer(texture);
}

UniqueRef<rcRenderBuffer> rcRenderBuffer::CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, Graphics::PixelFormat format)
{
  return Application::GetPlatform()->GetGraphicsAPI()->CreateDepthStencilBuffer(width, height, format);
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
  Application::GetPlatform()->GetGraphicsAPI()->DeleteRenderBuffer(this);
}