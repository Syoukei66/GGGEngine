#include "DefaultMeshAssetEntity.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_2(DefaultMeshAssetEntity, AssetMetaData* meta, StaticMeshData* data)
{
  this->data_ = data;
  return AssetEntity::Init(meta);
}

GG_DESTRUCT_FUNC_IMPL(DefaultMeshAssetEntity)
{
  delete this->data_;
  return true;
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void DefaultMeshAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcMesh>(uid, extension, rcMesh::Create(*this->data_));
}
