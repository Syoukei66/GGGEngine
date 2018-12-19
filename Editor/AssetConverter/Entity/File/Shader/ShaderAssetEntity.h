#pragma once

#include <Entity/File/FileAssetEntity.h>
#include <Entity/File/FileAssetConverterFactory.h>

class ShaderAssetEntity : public FileAssetEntity<ShaderData, rcShader>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_SHADER);
  GG_OBJECT(ShaderAssetEntity);
  GG_CREATE_FUNC_2(ShaderAssetEntity, AssetMetaData*, ShaderData*)
  {
    return FileAssetEntity<ShaderData, rcShader>::Init(arg0, arg1);
  }

  // =================================================================
  // Methods from RawAssetEntity
  // =================================================================
public:
  static IAssetConverter* CreateConverter();

};