#pragma once

#include "../Core/MeshData.h"
#include "AssetEntity.h"

class ModelMeshAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_MODEL_MESH)
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelMeshAssetEntity(AssetInfo* info, MeshData* data, T_UINT32 model_unique_id);
  ~ModelMeshAssetEntity();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const MeshData* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MeshData* data_;
  T_UINT32 model_unique_id_;

};