#pragma once

#include <assimp\scene.h>
#include <Entity/AssetEntity.h>
#include <Entity/File/Model/Mesh/ModelMeshAssetEntity.h>

class ModelAssetEntity : public AssetEntity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_MODEL);
  GG_OBJECT(ModelAssetEntity);
  GG_CREATE_FUNC_3(ModelAssetEntity, AssetInfo*, ModelData*, const aiScene*);
  GG_DESTRUCT_FUNC(ModelAssetEntity);

  // =================================================================
  // Methods from AssetEntity
  // =================================================================
public:
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const override;

  // =================================================================
  // Methods
  // =================================================================
public:
  void SetMeshReference(ModelMeshAssetEntity* mesh_entity);
  
  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const aiScene* GetScene() const
  {
    return this->scene_;
  }

  inline const ModelData* GetData() const
  {
    return this->data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  const aiScene* scene_;
  ModelData* data_;

};