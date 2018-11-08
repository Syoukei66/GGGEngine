#include "TextureAssetExporter.h"
#include <Util/FileUtil.h>

// =================================================================
// Methods
// =================================================================
void TextureAssetExporter::ExportProcess(TextureAssetEntity* entity, const AssetConverterContext* context)
{
  FileUtil::CopyRawAsset(entity->GetAssetInfo());
}
