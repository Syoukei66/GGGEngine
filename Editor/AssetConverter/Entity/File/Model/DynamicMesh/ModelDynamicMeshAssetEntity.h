#pragma once

#include <Entity/File/FileAssetEntity.h>
#include <Entity/File/FileAssetConverterFactory.h>

class ModelDynamicMeshAssetEntity : public FileAssetEntity<DynamicMeshData, rcDynamicMesh>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_MODEL_DYNAMIC_MESH);
  GG_OBJECT(ModelDynamicMeshAssetEntity);
  GG_CREATE_FUNC_2(ModelDynamicMeshAssetEntity, AssetMetaData*, DynamicMeshData*)
  {
    return FileAssetEntity<DynamicMeshData, rcDynamicMesh>::Init(arg0, arg1);
  }

  // =================================================================
  // Methods from RawAssetEntity
  // =================================================================
public:
  static inline IAssetConverter* CreateConverter()
  {
    return FileAssetConverterFactory::Create<ModelDynamicMeshAssetEntity>(nullptr, "ModelDynamicMesh", "rcDynamicMesh", 1, 0);
  }

};