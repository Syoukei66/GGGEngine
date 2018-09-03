#include "Texture.h"
#include "NativeProcess.h"

// =================================================================
// Factory Method
// =================================================================
rcTexture* rcTexture::CreateFromFile(const char* path)
{
  return NativeProcess::Resource::TextureLoad(path);
}

rcTexture* rcTexture::Create(T_UINT16 width, T_UINT16 height, void* native_obj)
{
  rcTexture* ret = new rcTexture(width, height, native_obj);
  ret->Resource::Init();
  return ret;
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
  this->color_buffer_ = rcRenderBuffer::CreateColorBuffer(this);
}

rcTexture::~rcTexture()
{
  this->color_buffer_->Release();
  NativeProcess::Resource::DeleteTexture(this);
}