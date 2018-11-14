#include "TextureAssetImporter.h"

// =================================================================
// Constructor / Destructor
// =================================================================
TextureAssetImporter::TextureAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================
SharedRef<TextureAssetEntity> TextureAssetImporter::ImportProcess(AssetInfo* info, AssetConverterContext* context)
{
  return TextureAssetEntity::Create(info);
}
