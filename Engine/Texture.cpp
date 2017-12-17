#include "Texture.h"
#include "NativeType.h"
#include "NativeMethod.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Texture::Texture(const std::string& path)
  : path_(path)
  , native_texture_(nullptr)
  , size_(-1, -1)
{
}

Texture::~Texture()
{
  this->Unload();
}

// =================================================================
// Methods
// =================================================================
void Texture::Load()
{
  if (this->IsLoaded())
  {
    return;
  }
  this->native_texture_ = new NativeTexture(this->path_.c_str());
}

void Texture::Unload()
{
  if (!this->IsLoaded())
  {
    return;
  }
  delete this->native_texture_;
  this->native_texture_ = nullptr;
  this->size_ = TSize(0, 0);
}
