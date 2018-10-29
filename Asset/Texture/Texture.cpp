#include "Texture.h"

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcTexture> rcTexture::CreateFromFile(const char* path)
{
  return NativeProcess::Resource::TextureLoad(path);
}

UniqueRef<rcTexture> rcTexture::Create(T_UINT16 width, T_UINT16 height, void* native_obj)
{
  return UniqueRef<rcTexture>(new rcTexture(width, height, native_obj));
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcTexture::rcTexture(T_UINT16 width, T_UINT16 height, void* native_obj)
  : native_obj_(native_obj)
  , width_(width)
  , height_(height)
{
  NativeProcess::Resource::GetTextureSize(this, &this->two_powered_width_, &this->two_powered_height_);
  this->color_buffer_ = rcRenderBuffer::CreateColorBuffer(SharedRef<rcTexture>(this));
}

rcTexture::~rcTexture()
{
  NativeProcess::Resource::DeleteTexture(this);
}