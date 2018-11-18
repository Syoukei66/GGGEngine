#include "StaticModelAssetEntity.h"
#include <Util/FileUtil.h>
#include <Entity/AssetMetaData.h>
#include <Assimp/cimport.h>

// =================================================================
// Constructor / Destructor
// =================================================================
GG_INIT_FUNC_IMPL_2(StaticModelAssetEntity, AssetMetaData* meta, StaticModelData* data)
{
  this->data_ = data;
  return AssetEntity::Init(meta);
}

GG_DESTRUCT_FUNC_IMPL(StaticModelAssetEntity)
{
  delete this->data_;
  return true;
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void StaticModelAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcStaticModel>(uid, extension, rcStaticModel::Create(*this->data_));
}

