#include "TextureAssetEntity.h"
#include <Entity/AssetInfo.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(TextureAssetEntity, AssetInfo* info)
{
  return AssetEntity::Init(info);
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void TextureAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcTexture>(uid, extension, rcTexture::CreateFromFile(this->GetAssetInfo()->GetInputPath().c_str()));
}
