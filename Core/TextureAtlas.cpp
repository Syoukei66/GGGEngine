#include "TextureAtlas.h"
#include "TextureAtlasLoader.h"

// =================================================================
// Factory Method
// =================================================================
rcTextureAtlas* rcTextureAtlas::CreateFromFile(const char* path)
{
  NATIVE_ASSERT(false, "‚Ü‚¾‚Å‚«‚Ä‚Ü‚¹‚ñI");
  //std::string directory_path = std::string();
  //if (strlen(asset_root) > 0)
  //{
  //  directory_path.append(asset_root);
  //  directory_path.append("/");
  //}
  //if (strlen(asset_particle) > 0)
  //{
  //  directory_path.append(asset_particle);
  //  directory_path.append("/");
  //}
  //TextureAtlasLoader loader;
  //return loader.Load(directory_path.c_str(), path);
  return nullptr;
}

rcTextureAtlas* rcTextureAtlas::Create(const rcTexture* texture)
{
  rcTextureAtlas* ret = new rcTextureAtlas(texture);
  ret->Resource::Init();
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcTextureAtlas::rcTextureAtlas(const rcTexture* texture)
  : texture_(texture)
{
  this->texture_->Retain();
}

rcTextureAtlas::~rcTextureAtlas()
{
  this->texture_->Release();
}

// =================================================================
// Method
// =================================================================
void rcTextureAtlas::Register(const std::string& path, rcTextureRegion* region)
{
  region->Retain();
  const auto& already = this->region_map_.find(path);
  if (already != this->region_map_.end())
  {
    already->second->Release();
  }
  this->region_map_[path] = region;
}

