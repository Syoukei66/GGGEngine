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
