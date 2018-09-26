#include "ModelAssetEntity.h"
#include "FileUtil.h"
#include "AssetInfo.h"

// =================================================================
// Factory Method
// =================================================================
ModelAssetEntity* ModelAssetEntity::Create(AssetInfo* info, ModelData* data, const aiScene* scene)
{
  return new ModelAssetEntity(info, data, scene);
}

// =================================================================
// Constructor / Destructor
// =================================================================
ModelAssetEntity::ModelAssetEntity(AssetInfo* info, ModelData* data, const aiScene* scene)
  : AssetEntity(info)
  , scene_(scene)
  , data_(data)
{
}

// =================================================================
// Methods
// =================================================================
void ModelAssetEntity::SetMeshReference(ModelMeshAssetEntity* mesh_entity)
{
  this->data_->mesh_unique_id_ = mesh_entity->GetAssetInfo()->GetUniqueID();
}
