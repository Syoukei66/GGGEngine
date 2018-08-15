#include "Texture.h"
#include "NativeProcess.h"

Texture* Texture::Create(const char* path)
{
  T_UINT16 width = 0.0f;
  T_UINT16 height = 0.0f;
  NativeProcess::Resource::GetTextureSize(path, &width, &height);
  return new Texture(width, height, NativeProcess::Resource::TextureLoad(path));
}

Texture* Texture::Create(T_UINT16 width, T_UINT16 height, void* native_obj)
{
  return new Texture(width, height, native_obj);
}

Texture::Texture(T_UINT16 width, T_UINT16 height, void* native_obj)
  : native_obj_(native_obj)
  , width_(width)
  , height_(height)
{
  NativeProcess::Resource::GetTextureSize(native_obj, &this->two_powered_width_, &this->two_powered_height_);
  this->color_buffer_ = RenderBuffer::CreateColorBuffer(this);
}

Texture::~Texture()
{
  delete this->color_buffer_;
  NativeProcess::Resource::DeleteTexture(this->native_obj_);
}