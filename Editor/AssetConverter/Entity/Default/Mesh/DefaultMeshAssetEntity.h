#pragma once

#include <Entity/AssetEntity.h>

class DefaultMeshAssetEntity : public AssetEntity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_DEFAULT_MESH);
  GG_OBJECT(DefaultMeshAssetEntity);
  GG_CREATE_FUNC_2(DefaultMeshAssetEntity, AssetMetaData*, MeshData*);
  GG_DESTRUCT_FUNC(DefaultMeshAssetEntity);

  // =================================================================
  // Methods from AssetEntity
  // =================================================================
public:
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const MeshData* GetData() const
  {
    return this->data_;
  }

  inline MeshData* GetData() 
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MeshData* data_;

};
