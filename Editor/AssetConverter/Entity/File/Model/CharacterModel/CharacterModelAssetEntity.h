#pragma once

#include <Entity/File/FileAssetEntity.h>
#include <Entity/File/FileAssetConverterFactory.h>

class CharacterModelAssetEntity : public FileAssetEntity<CharacterModelData, rcCharacterModel>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_CHARACTER_MODEL);
  GG_OBJECT(CharacterModelAssetEntity);
  GG_CREATE_FUNC_2(CharacterModelAssetEntity, AssetMetaData*, CharacterModelData*)
  {
    return FileAssetEntity<CharacterModelData, rcCharacterModel>::Init(arg0, arg1);
  }

  // =================================================================
  // Methods from RawAssetEntity
  // =================================================================
public:
  static IAssetConverter* CreateConverter();

};
