#include "TextureAssetEntity.h"
#include <Entity/AssetMetaData.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(TextureAssetEntity, AssetMetaData* meta)
{
  return AssetEntity::Init(meta);
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void TextureAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcTexture>(uid, extension, rcTexture::CreateFromFile(this->GetMetaData()->GetInputPath().c_str()));
}
