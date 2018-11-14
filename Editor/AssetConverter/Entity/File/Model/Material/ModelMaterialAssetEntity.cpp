#include "ModelMaterialAssetEntity.h"

// =================================================================
// FactoryMethod
// =================================================================
GG_INIT_FUNC_IMPL_2(ModelMaterialAssetEntity, AssetInfo* info, MaterialData* data)
{
  this->data_ = data;
  return AssetEntity::Init(info);
}

GG_DESTRUCT_FUNC_IMPL(ModelMaterialAssetEntity)
{
  delete this->data_;
  return true;
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void ModelMaterialAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string& extension) const
{
  AssetManager::AddAsset<rcMaterial>(uid, extension, rcMaterial::Create(*this->data_));
}
