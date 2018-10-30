#pragma once

#include "AssetEntity.h"

class ModelMaterialAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_MODEL_MATERIAL)
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelMaterialAssetEntity(AssetInfo* info, MaterialData* data, T_UINT32 model_unique_id);
  ~ModelMaterialAssetEntity();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const MaterialData* GetData() const
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