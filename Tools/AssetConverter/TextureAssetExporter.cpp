#include "TextureAssetExporter.h"
#include "FileUtil.h"

// =================================================================
// Methods
// =================================================================
void TextureAssetExporter::ExportProcess(TextureAssetEntity* entity, const AssetConverterContext* context)
{
  FileUtil::CopyRawAsset(entity->GetAssetInfo());
}
