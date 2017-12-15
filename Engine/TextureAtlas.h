#pragma once

#include <map>
#include <string>
#include "NativeType.h"
#include "Geometry.h"
#include "TextureRegion.h"

struct AtlasRegion
{
  AtlasRegion()
    : rotate(false)
    , area()
  {}
  bool rotate;
  TArea area;
};

class TextureAtlas
{
public:
  static TextureAtlas* CreateWithAtlasFile(const char* path);

public:
  TextureAtlas(const ITexture* texture);

public:
  void Register(const std::string& path, const AtlasRegion& region);

  //受け取ったTextureRegionは使用後に解放する事
  TextureRegion* GetTextureRegion(const std::string& path) const;

private:
  const ITexture* texture_;
  std::map<std::string, AtlasRegion> region_map_;
};
