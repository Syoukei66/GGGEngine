#pragma once

#include <map>
#include <string>
#include "../Core/NativeType.h"
#include "../Core/Geometry.h"
#include "TextureRegion.h"

/*
  TODO: Resource�Ǘ����@�̕ύX�ɖ��Ή�
*/

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
  TextureAtlas(const rcTexture* texture);

public:
  void Register(const std::string& path, const AtlasRegion& region);

  //�󂯎����TextureRegion�͎g�p��ɉ�����鎖
  TextureRegion* GetTextureRegion(const std::string& path) const;

private:
  const rcTexture* texture_;
  std::map<std::string, AtlasRegion> region_map_;
};
