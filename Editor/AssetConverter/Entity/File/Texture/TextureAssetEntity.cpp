#include "TextureAssetEntity.h"
#include <Entity/AssetInfo.h>

// =================================================================
// Constructor / Destructor
// =================================================================
TextureAssetEntity::TextureAssetEntity(AssetInfo* info)
  : AssetEntity(info)
{
}

// =================================================================
// Methods from AssetEntity
// =================================================================
void TextureAssetEntity::RegisterAssetManager(T_UINT32 uid, const std::string & extension) const
{
  AssetManager::AddAsset<rcTexture>(uid, extension, rcTexture::CreateFromFile(this->GetAssetInfo()->GetInputPath().c_str()));
}
