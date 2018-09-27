#include "ModelAssetEntity.h"
#include "FileUtil.h"
#include "AssetInfo.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelAssetEntity::ModelAssetEntity(AssetInfo* info, ModelData* data, const aiScene* scene)
  : AssetEntity(info)
  , scene_(scene)
  , data_(data)
{
}

ModelAssetEntity::~ModelAssetEntity()
{
  delete this->data_;
}

// =================================================================
// Methods
// =================================================================
void ModelAssetEntity::SetMeshReference(ModelMeshAssetEntity* mesh_entity)
{
  this->data_->mesh_unique_id_ = mesh_entity->GetAssetInfo()->GetUniqueID();
}
