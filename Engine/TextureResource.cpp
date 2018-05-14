#include "TextureResource.h"
#include "NativeType.h"
#include "UserResourcePool.h"

TextureResource* TextureResource::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<TextureResource>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
TextureResource::TextureResource(const char* path)
  : FileResource("Texture", path)
{}

// =================================================================
// Methods
// =================================================================
INativeTexture* TextureResource::NativeLoadProcess(const std::string& path)
{
  return INativeTexture::Create(path.c_str());
}
