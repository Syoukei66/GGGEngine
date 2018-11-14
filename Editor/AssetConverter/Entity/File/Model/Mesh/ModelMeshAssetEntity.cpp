#include "ModelMeshAssetEntity.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelMeshAssetEntity::ModelMeshAssetEntity(AssetInfo* info, MeshData* data)
  : AssetEntity(info)
  , data_(data)
{
}

ModelMeshAssetEntity::~ModelMeshAssetEntity()
{
  delete this->data_;
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void ModelMeshAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcMesh>(uid, extension, rcMesh::Create(*this->data_));
}
