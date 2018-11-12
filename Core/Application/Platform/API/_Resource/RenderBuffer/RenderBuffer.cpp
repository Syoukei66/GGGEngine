#include "RenderBuffer.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcRenderBuffer, void* native_obj)
{
  this->native_obj_ = native_obj;
  return true;
}

GG_DESTRUCT_FUNC_IMPL(rcRenderBuffer)
{
  Application::GetPlatform()->GetGraphicsAPI()->DeleteRenderBuffer(this);
  return true;
}

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

