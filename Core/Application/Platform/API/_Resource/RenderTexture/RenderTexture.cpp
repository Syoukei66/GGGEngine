#include "RenderTexture.h"
#include <Core/Application/Platform/API/_Resource/RenderBuffer/RenderBuffer.h>

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcRenderTexture> rcRenderTexture::Create(T_UINT16 width, T_UINT16 height, Graphics::PixelFormat format)
{
  return Application::GetPlatform()->GetGraphicsAPI()->CreateRenderTexture(width, height, format, Graphics::PixelFormat::FORMAT_D16);
}

UniqueRef<rcRenderTexture> rcRenderTexture::Create(T_UINT16 width, T_UINT16 height, Graphics::PixelFormat format, Graphics::PixelFormat depth_format)
{
  return Application::GetPlatform()->GetGraphicsAPI()->CreateRenderTexture(width, height, format, depth_format);
}

UniqueRef<rcRenderTexture> rcRenderTexture::Create(T_UINT16 width, T_UINT16 height, void* native_obj, Graphics::PixelFormat depth_format)
{
  return UniqueRef<rcRenderTexture>(new rcRenderTexture(width, height, native_obj, depth_format));
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcRenderTexture::rcRenderTexture(T_UINT16 width, T_UINT16 height, void* native_obj, Graphics::PixelFormat depth_format)
  : rcTexture(width, height, native_obj)
{
  this->depth_stencil_buffer_ = rcRenderBuffer::CreateDepthStencilBuffer(this->GetTwoPoweredWidth(), this->GetTwoPoweredHeight(), depth_format);
}

// =================================================================
// Methods
// =================================================================
void rcRenderTexture::RenderBegin(bool clear)
{
  Application::GetPlatform()->GetGraphicsAPI()->SetRenderTarget(this->GetColorBuffer(), this->depth_stencil_buffer_, clear);
}

void rcRenderTexture::RenderEnd()
{
  Application::GetPlatform()->GetGraphicsAPI()->ResetRenderTarget();
}
