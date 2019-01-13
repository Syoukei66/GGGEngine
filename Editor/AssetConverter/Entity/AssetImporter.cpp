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

AssetImporter::~AssetImporter()
{
  for (const auto& pair : this->reserve_assets_)
  {
    delete pair.second;
  }
}

// =================================================================
// Methods
// =================================================================
bool AssetImporter::IsTarget(const URI& uri)
{
  return std::find(this->target_extensions_.begin(), this->target_extensions_.end(), uri.GetExtension()) != this->target_extensions_.end();
}

bool AssetImporter::Reserve(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context)
{
  //対応する拡張子かチェック
  if (!this->IsTarget(uri))
  {
    return false;
  }
  AssetMetaData* meta = AssetMetaData::Create(uri, source_unique_id, context);
  this->reserve_assets_[meta->GetUniqueID()] = meta;
  return true;
}

void* AssetImporter::ImportImmediately(AssetMetaData* meta_data, AssetConverterContext* context)
{
  return this->ImportProcess(meta_data, context);
}


