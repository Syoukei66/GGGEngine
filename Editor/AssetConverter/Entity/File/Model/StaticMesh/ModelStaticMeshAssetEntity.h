#pragma once

#include <Entity/File/FileAssetEntity.h>
#include <Entity/File/FileAssetConverterFactory.h>

class ModelStaticMeshAssetEntity : public FileAssetEntity<StaticMeshData, rcMesh>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_MODEL_STATIC_MESH);
  GG_OBJECT(ModelStaticMeshAssetEntity);
  GG_CREATE_FUNC_2(ModelStaticMeshAssetEntity, AssetMetaData*, StaticMeshData*)
  {
    return FileAssetEntity<StaticMeshData, rcMesh>::Init(arg0, arg1);
  }

  // =================================================================
  // Methods from RawAssetEntity
  // =================================================================
public:
  static inline IAssetConverter* CreateConverter()
  {
    return FileAssetConverterFactory::Create<ModelStaticMeshAssetEntity>(nullptr, "ModelStaticMesh", "rcMesh", 1, 0);
  }

};