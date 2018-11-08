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
