#pragma once

#include <assimp\scene.h>
#include <Core/ModelData.h>
#include "AssetEntity.h"
#include "ModelMeshAssetEntity.h"

class ModelAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_MODEL)
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelAssetEntity(AssetInfo* info, ModelData* data, const aiScene* scene);
  ~ModelAssetEntity();

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