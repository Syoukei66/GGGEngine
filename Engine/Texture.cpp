#include "Texture.h"
#include "NativeType.h"
#include "UserResourcePool.h"

Texture* Texture::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<Texture>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
Texture::Texture(const char* path)
  : FileResource("Texture", path)
{}

// =================================================================
// Methods
// =================================================================
INativeTexture* Texture::NativeLoadProcess(const std::string& path)
{
  return INativeTexture::Create(path.c_str());
}
