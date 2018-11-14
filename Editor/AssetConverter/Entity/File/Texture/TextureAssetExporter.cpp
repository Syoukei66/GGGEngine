#include "TextureAssetExporter.h"
#include <Util/FileUtil.h>

// =================================================================
// Methods
// =================================================================
void TextureAssetExporter::ExportProcess(const SharedRef<TextureAssetEntity>& entity, const AssetConverterContext* context)
{
  FileUtil::CopyRawAsset(entity->GetAssetInfo());
}
