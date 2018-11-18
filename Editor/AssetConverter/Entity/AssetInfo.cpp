#include <Entity/AssetInfo.h>
#include <regex>
#include <fstream>
#include <Util/FileUtil.h>
#include <Converter/AssetConverter.h>
#include <Converter/AssetConverterContext.h>

// =================================================================
// Factory Method
// =================================================================
AssetInfo* AssetInfo::Create(const URI& uri, AssetConverterContext* context)
{
  return new AssetInfo(AssetMetaData::Create(uri, context));
}

AssetInfo* AssetInfo::Create(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context)
{
  return new AssetInfo(AssetMetaData::Create(uri, source_unique_id, context));
}

// =================================================================
// Constructor / Destructor
// =================================================================
AssetInfo::AssetInfo(AssetMetaData* meta_data)
  : meta_data_(meta_data)
{
}

AssetInfo::~AssetInfo()
{
  delete this->meta_data_;
}

