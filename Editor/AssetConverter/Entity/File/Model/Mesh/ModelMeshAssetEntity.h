#pragma once

#include <Entity/File/FileAssetEntity.h>

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

};