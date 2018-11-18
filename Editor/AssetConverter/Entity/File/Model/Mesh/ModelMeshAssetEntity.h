#pragma once

#include <Entity/AssetEntity.h>

class ModelMeshAssetEntity : public AssetEntity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_MODEL_MESH);
  GG_OBJECT(ModelMeshAssetEntity);
  GG_CREATE_FUNC_2(ModelMeshAssetEntity, AssetMetaData*, MeshData*);
  GG_DESTRUCT_FUNC(ModelMeshAssetEntity);

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