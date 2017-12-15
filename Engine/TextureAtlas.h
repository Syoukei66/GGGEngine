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

  //Žó‚¯Žæ‚Á‚½TextureRegion‚ÍŽg—pŒã‚É‰ð•ú‚·‚éŽ–
  TextureRegion* GetTextureRegion(const std::string& path) const;

private:
  const ITexture* texture_;
  std::map<std::string, AtlasRegion> region_map_;
};
