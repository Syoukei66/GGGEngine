#pragma once

#include <Entity/File/FileAssetEntity.h>
#include <Entity/File/FileAssetConverterFactory.h>

class ModelMaterialAssetEntity : public FileAssetEntity<MaterialData, rcMaterial>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_MODEL_MATERIAL);
  GG_OBJECT(ModelMaterialAssetEntity);
  GG_CREATE_FUNC_2(ModelMaterialAssetEntity, AssetMetaData*, MaterialData*)
  {
    return FileAssetEntity<MaterialData, rcMaterial>::Init(arg0, arg1);
  }

  // =================================================================
  // Methods from RawAssetEntity
  // =================================================================
public:
  static inline IAssetConverter* CreateConverter()
  {
    return FileAssetConverterFactory::Create<ModelMaterialAssetEntity>(nullptr, "ModelMaterial", "rcMaterial", 1, 0);
  }

};