#pragma once

#include <Entity/File/FileAssetEntity.h>
#include <Entity/File/FileAssetConverterFactory.h>

class TextureAssetEntity : public FileAssetEntity<TextureData, rcTexture>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_TEXTURE);
  GG_OBJECT(TextureAssetEntity);
  GG_CREATE_FUNC_2(TextureAssetEntity, AssetMetaData*, TextureData*)
  {
    return FileAssetEntity<TextureData, rcTexture>::Init(arg0, arg1);
  }

  // =================================================================
  // Methods from RawAssetEntity
  // =================================================================
public:
  static IAssetConverter* CreateConverter();

};
