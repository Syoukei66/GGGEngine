#include "TextureAtlas.h"
#include "Director.h"
#include "TextureAtlasLoader.h"

TextureAtlas* TextureAtlas::CreateWithAtlasFile(const char* path)
{
  std::string directory_path = std::string();
  const char* asset_root = Director::GetInstance()->GetEngineOption()->asset_path.root;
  const char* asset_particle = Director::GetInstance()->GetEngineOption()->asset_path.particle;
  if (strlen(asset_root) > 0)
  {
    directory_path.append(asset_root);
    directory_path.append("/");
  }
  if (strlen(asset_particle) > 0)
  {
    directory_path.append(asset_particle);
    directory_path.append("/");
  }
  TextureAtlasLoader loader;
  return loader.Load(directory_path.c_str(), path);
}

TextureAtlas::TextureAtlas(const ITexture* texture)
  : texture_(texture)
{}

void TextureAtlas::Register(const std::string& path, const AtlasRegion& region)
{
  this->region_map_[path] = region;
}

TextureRegion* TextureAtlas::GetTextureRegion(const std::string& path) const
{
  TextureRegion* ret = new TextureRegion();
  ret->SetTexture(this->texture_);
  const AtlasRegion& region = this->region_map_.at(path);
  ret->SetX((T_FLOAT)region.area.pos.x);
  ret->SetY((T_FLOAT)region.area.pos.y);
  ret->SetWidth((T_FLOAT)region.area.size.width);
  ret->SetHeight((T_FLOAT)region.area.size.height);
  return ret;
}
