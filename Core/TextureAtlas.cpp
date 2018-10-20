#include "TextureAtlas.h"
#include "TextureAtlasLoader.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcTextureAtlas> rcTextureAtlas::CreateFromFile(const char* path)
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
  return UniqueResource<rcTextureAtlas>();
}

UniqueResource<rcTextureAtlas> rcTextureAtlas::Create(const SharedRef<const rcTexture>& texture)
{
  rcTextureAtlas* ret = new rcTextureAtlas(texture);
  ret->Resource::Init();
  return UniqueResource<rcTextureAtlas>(ret);
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcTextureAtlas::rcTextureAtlas(const SharedRef<const rcTexture>& texture)
{
  this->texture_ = texture;
}

rcTextureAtlas::~rcTextureAtlas()
{
}

// =================================================================
// Method
// =================================================================
void rcTextureAtlas::Register(const std::string& path, const SharedRef<rcTextureRegion>& region)
{
  this->region_map_[path] = region;
}

