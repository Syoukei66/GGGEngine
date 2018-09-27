#include "AssetMetaData.h"
#include <fstream>

#include "../Core/CerealIO.h"
#include "FileUtil.h"
#include "Director.h"
#include "Extensions.h"

// =================================================================
// Factory Method
// =================================================================
AssetMetaData* AssetMetaData::Create(const URI& uri, AssetConverterContext* context)
{
  const std::string path = FileUtil::CreateInputPath(uri.GetFullPath() + "." + Extensions::META);
  if (!std::ifstream(path).is_open())
  {
    return new AssetMetaData(uri, context);
  }
  AssetMetaData* ret = CerealIO::Json::SafeImport<AssetMetaData>(path.c_str());
  if (!ret)
  {
    ret = new AssetMetaData(uri, context);
  }
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
AssetMetaData::AssetMetaData(const URI& uri, AssetConverterContext* context)
  : uri_(this->uri_)
{
  this->unique_id_ = context->PublishUniqueID(uri);
}

AssetMetaData::AssetMetaData()
  : uri_("")
{
}

// =================================================================
// Methods
// =================================================================
void AssetMetaData::Save()
{
  const std::string path = FileUtil::CreateInputPath(this->uri_.GetFullPath() + "." + Extensions::META);
  CerealIO::Json::Export(path.c_str(), this);
}

AssetMetaData* AssetMetaData::CreateChild(const std::string& child_path, AssetConverterContext* context)
{
  AssetMetaData* ret = new AssetMetaData(child_path, context);
  ret->source_ = this->unique_id_;
  this->related_unique_ids_.emplace(ret->unique_id_);
  return ret;
}

void AssetMetaData::ResetTimeStamp()
{
  this->time_stamp_ = "";
}

bool AssetMetaData::UpdateTimeStamp()
{
  const std::string time_stamp = FileUtil::GetTimeStamp(FileUtil::CreateInputPath(this->uri_.GetFullPath()));
  const bool asset_changed = time_stamp != this->time_stamp_;
  if (asset_changed)
  {
    this->time_stamp_ = time_stamp;
  }
  return asset_changed;
}
