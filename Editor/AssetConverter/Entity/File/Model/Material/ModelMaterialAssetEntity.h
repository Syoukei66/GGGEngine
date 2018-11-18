#pragma once

#include <Entity/AssetEntity.h>

class ModelMaterialAssetEntity : public AssetEntity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_MODEL_MATERIAL);
  GG_OBJECT(ModelMaterialAssetEntity);
  GG_CREATE_FUNC_2(ModelMaterialAssetEntity, AssetMetaData*, MaterialData*);
  GG_DESTRUCT_FUNC(ModelMaterialAssetEntity);

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

};