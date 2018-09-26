#pragma once

#include <assimp\scene.h>
#include "../Core/ModelData.h"
#include "AssetEntity.h"
#include "ModelMeshAssetEntity.h"

class ModelAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_MODEL)
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static ModelAssetEntity* Create(AssetInfo* info, ModelData* data, const aiScene* scene);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  ModelAssetEntity(AssetInfo* info, ModelData* data, const aiScene* scene);

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

  // =================================================================
  // Data Members
  // =================================================================
private:
  const aiScene* scene_;
  ModelData* data_;

};