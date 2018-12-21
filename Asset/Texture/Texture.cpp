#include "Texture.h"
#include <Core/Application/Platform/API/_Resource/RenderBuffer/RenderBuffer.h>

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcTexture> rcTexture::CreateFromFile(const char* path)
{
  return Application::GetPlatform()->GetGraphicsAPI()->TextureLoad(path);
}

UniqueRef<rcTexture> rcTexture::Create(T_UINT16 width, T_UINT16 height, const SharedRef<rcTextureResource>& texture_resource)
{
  return UniqueRef<rcTexture>(new rcTexture(width, height, texture_resource));
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcTexture::rcTexture(T_UINT16 width, T_UINT16 height, const SharedRef<rcTextureResource>& texture_resource)
  : resource_(texture_resource)
  , width_(width)
  , height_(height)
{
  Application::GetPlatform()->GetGraphicsAPI()->GetTextureSize(this, &this->two_powered_width_, &this->two_powered_height_);
  this->color_buffer_ = rcRenderBuffer::CreateColorBuffer(SharedRef<rcTexture>(this));
}

rcTexture::~rcTexture()
{
  Application::GetPlatform()->GetGraphicsAPI()->DeleteTexture(this);
}
