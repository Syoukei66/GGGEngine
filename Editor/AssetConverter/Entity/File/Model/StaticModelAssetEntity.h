#pragma once

#include <Entity/AssetEntity.h>

class StaticModelAssetEntity : public AssetEntity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_STATIC_MODEL);
  GG_OBJECT(StaticModelAssetEntity);
  GG_CREATE_FUNC_2(StaticModelAssetEntity, AssetMetaData*, StaticModelData*);
  GG_DESTRUCT_FUNC(StaticModelAssetEntity);

  // =================================================================
  // Methods from AssetEntity
  // =================================================================
public:
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const StaticModelData* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  StaticModelData* data_;

};