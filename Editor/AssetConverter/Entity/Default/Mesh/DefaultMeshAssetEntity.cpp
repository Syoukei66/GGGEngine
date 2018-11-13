#include "DefaultMeshAssetEntity.h"

// =================================================================
// Constructor / Destructor
// =================================================================
DefaultMeshAssetEntity::DefaultMeshAssetEntity(AssetInfo* info, MeshData* data)
  : AssetEntity(info)
  , data_(data)
{
}

DefaultMeshAssetEntity::~DefaultMeshAssetEntity()
{
  delete this->data_;
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void DefaultMeshAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcMesh>(uid, extension, rcMesh::Create(*this->data_));
}
