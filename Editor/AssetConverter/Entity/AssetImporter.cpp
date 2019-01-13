#include "AssetImporter.h"
#include <Entity/AssetMetaData.h>
#include <Converter/AssetConverterContext.h>

// =================================================================
// Constructor / Destructor
// =================================================================
AssetImporter::AssetImporter(const std::vector<std::string>& extensions)
  : target_extensions_(extensions)
{
}

// =================================================================
// Methods
// =================================================================
bool AssetImporter::IsTarget(const URI& uri)
{
  return std::find(this->target_extensions_.begin(), this->target_extensions_.end(), uri.GetExtension()) != this->target_extensions_.end();
}

void* AssetImporter::ImportImmediately(AssetMetaData* meta_data, AssetConverterContext* context)
{
  return this->ImportProcess(meta_data, context);
}


