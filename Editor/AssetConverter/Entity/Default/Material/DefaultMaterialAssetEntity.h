#pragma once

#include <Entity/AssetEntity.h>

class DefaultMaterialAssetEntity : public AssetEntity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_DEFAULT_MATERIAL);
  GG_OBJECT(DefaultMaterialAssetEntity);
  GG_CREATE_FUNC_2(DefaultMaterialAssetEntity, AssetMetaData*, MaterialData*);
  GG_DESTRUCT_FUNC(DefaultMaterialAssetEntity);

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
