#include "Texture.h"
#include "NativeType.h"
#include "ResourcePool.h"

const Texture* Texture::DynamicLoad(const char* path)
{
  return ResourcePool::GetInstance().DynamicLoad<Texture>(path);
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
