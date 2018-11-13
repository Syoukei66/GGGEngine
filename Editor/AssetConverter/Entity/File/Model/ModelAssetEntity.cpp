#include "ModelAssetEntity.h"
#include <Util/FileUtil.h>
#include <Entity/AssetInfo.h>
#include <Assimp/cimport.h>

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
  aiReleaseImport(this->scene_);
  delete this->data_;
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void ModelAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcModel>(uid, extension, rcModel::Create(*this->data_));
}

// =================================================================
// Methods
// =================================================================
void ModelAssetEntity::SetMeshReference(ModelMeshAssetEntity* mesh_entity)
{
  this->data_->mesh_unique_id_ = mesh_entity->GetAssetInfo()->GetUniqueID();
}
