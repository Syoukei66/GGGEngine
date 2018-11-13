#include "DefaultMaterialAssetEntity.h"

// =================================================================
// Constructor / Destructor
// =================================================================
DefaultMaterialAssetEntity::DefaultMaterialAssetEntity(AssetInfo* info, MaterialData* data)
  : AssetEntity(info)
  , data_(data)
{
}

DefaultMaterialAssetEntity::~DefaultMaterialAssetEntity()
{
  delete this->data_;
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void DefaultMaterialAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcMaterial>(uid, extension, rcMaterial::Create(*this->data_));
}
