#include "AssetInfo.h"
#include <regex>
#include <fstream>
#include "FileUtil.h"
#include "AssetConverter.h"
#include "AssetConverterContext.h"

// =================================================================
// Factory Method
// =================================================================
AssetInfo* AssetInfo::Create(const URI& uri, AssetConverterContext* context)
{
  AssetInfo* ret = new AssetInfo(uri);
  ret->meta_data_ = AssetMetaData::Create(uri, context);
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
AssetInfo::AssetInfo(const URI& uri)
  : uri_(uri)
{
}

AssetInfo::~AssetInfo()
{
  delete this->meta_data_;
}

