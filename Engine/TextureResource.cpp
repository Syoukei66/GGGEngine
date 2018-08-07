#include "TextureResource.h"
#include "../Common/NativeType.h"
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
Texture* TextureResource::NativeLoadProcess(const std::string& path)
{
  return Texture::Create(path.c_str());
}
