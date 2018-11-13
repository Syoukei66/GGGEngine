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

// =================================================================
// Methods from AssetEntity
// =================================================================
void ModelMaterialAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string& extension) const
{
  AssetManager::AddAsset<rcMaterial>(uid, extension, rcMaterial::Create(*this->data_));
}
