#include "DefaultMeshAssetEntity.h"

// =================================================================
// Constructor / Destructor
// =================================================================
DefaultMeshAssetEntity::DefaultMeshAssetEntity(AssetInfo* info, MeshData* data, T_UINT32 default_unique_id)
  : AssetEntity(info)
  , data_(data)
  , default_unique_id_(default_unique_id)
{

}


DefaultMeshAssetEntity::~DefaultMeshAssetEntity()
{
  delete this->data_;
}
