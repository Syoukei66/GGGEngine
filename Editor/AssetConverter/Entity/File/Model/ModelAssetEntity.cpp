#include "ModelAssetEntity.h"
#include <Util/FileUtil.h>
#include <Entity/AssetInfo.h>
#include <Assimp/cimport.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INIT_FUNC_IMPL_3(ModelAssetEntity, AssetInfo* info, ModelData* data, const aiScene* scene)
{
  this->scene_ = scene;
  this->data_ = data;
  return AssetEntity::Init(info);
}

GG_DESTRUCT_FUNC_IMPL(ModelAssetEntity)
{
  aiReleaseImport(this->scene_);
  delete this->data_;
  return true;
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
