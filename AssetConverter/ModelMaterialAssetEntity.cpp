#include "ModelMaterialAssetEntity.h"

// =================================================================
// FactoryMethod
// =================================================================
ModelMaterialAssetEntity::ModelMaterialAssetEntity(AssetInfo* info, MaterialData* data, T_UINT32 model_unique_id)
  : AssetEntity(info)
  , data_(data)
{
}

ModelMaterialAssetEntity::~ModelMaterialAssetEntity()
{
  delete this->data_;
}
