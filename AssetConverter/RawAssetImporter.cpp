#include "RawAssetImporter.h"

// =================================================================
// Constructor / Destructor
// =================================================================
RawAssetImporter::RawAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================
RawAssetEntity* RawAssetImporter::ImportProcess(AssetInfo* info, AssetConverterContext* context)
{
  return new RawAssetEntity(info);
}
