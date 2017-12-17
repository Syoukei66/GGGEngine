#include "NativeTexture.h"
#include "NativeMethod.h"

NativeTexture::NativeTexture(const char* path)
  : NativeObject(NativeMethod::Texture().Texture_Load(path))
{
  NativeMethod::Texture().Texture_GetSize(this->instance_, &this->size_);
}

NativeTexture::~NativeTexture()
{
  NativeMethod::Texture().Texture_Unload(this->instance_);
}
