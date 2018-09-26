#pragma once

#include "../Core/MaterialData.h"
#include "AssetEntity.h"

class ModelMaterialAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_MODEL_MATERIAL)
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelMaterialAssetEntity(AssetInfo* info, MaterialData* data, T_UINT32 model_unique_id);

public:
  ~ModelMaterialAssetEntity();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline MaterialData* GetMaterialData()
  {
    return this->data_;
  }

  inline const MaterialData* GetMeshData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MaterialData* data_;
  T_UINT32 model_unique_id_;

};