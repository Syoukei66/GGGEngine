#pragma once

#include <Entity/AssetEntity.h>

class DefaultMaterialAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_DEFAULT_MATERIAL);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefaultMaterialAssetEntity(AssetInfo* info, MaterialData* data);
  ~DefaultMaterialAssetEntity();

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
