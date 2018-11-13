#pragma once

#include <Entity/AssetEntity.h>

class ModelMaterialAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_MODEL_MATERIAL);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelMaterialAssetEntity(AssetInfo* info, MaterialData* data, T_UINT32 model_unique_id);
  ~ModelMaterialAssetEntity();

  // =================================================================
  // Methods from AssetEntity
  // =================================================================
public:
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const override;

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