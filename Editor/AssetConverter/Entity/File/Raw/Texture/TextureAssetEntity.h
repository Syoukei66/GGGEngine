#pragma once

#include <Entity/File/Raw/RawAssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class TextureAssetEntity : public RawAssetEntity<rcTexture>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_TEXTURE);
  GG_OBJECT(TextureAssetEntity);
  GG_CREATE_FUNC_1(TextureAssetEntity, AssetMetaData*)
  {
    return AssetEntity::Init(arg0);
  }

  // =================================================================
  // Methods from RawAssetEntity
  // =================================================================
public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<TextureAssetEntity>("Texture", "rcTexture", "jpg", "png", "tga", "bmp", "jpeg");
  }

};
