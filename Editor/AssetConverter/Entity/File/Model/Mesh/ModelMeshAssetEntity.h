#pragma once

#include <Entity/File/FileAssetEntity.h>
#include <Entity/File/FileAssetConverterFactory.h>

class ModelMeshAssetEntity : public FileAssetEntity<MeshData, rcMesh>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_MODEL_MESH);
  GG_OBJECT(ModelMeshAssetEntity);
  GG_CREATE_FUNC_2(ModelMeshAssetEntity, AssetMetaData*, MeshData*)
  {
    return FileAssetEntity<MeshData, rcMesh>::Init(arg0, arg1);
  }

  // =================================================================
  // Methods from RawAssetEntity
  // =================================================================
public:
  static inline IAssetConverter* CreateConverter()
  {
    return FileAssetConverterFactory::Create<ModelMeshAssetEntity>(nullptr, "ModelMesh", "rcMesh", 1, 0);
  }

};