#include "ModelMeshAssetEntity.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelMeshAssetEntity::ModelMeshAssetEntity(AssetInfo* info, MeshData* data, T_UINT32 model_unique_id)
  : AssetEntity(info)
  , data_(data)
  , model_unique_id_(model_unique_id)
{
}

ModelMeshAssetEntity::~ModelMeshAssetEntity()
{
  delete this->data_;
}