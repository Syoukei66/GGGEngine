#include "AssetMetaData.h"
#include <fstream>

#include "../Core/CerealIO.h"
#include "FileUtil.h"
#include "Director.h"

static const char* META_DATA_EXTENSION = "meta";

// =================================================================
// Factory Method
// =================================================================
AssetMetaData* AssetMetaData::Create(const std::string& asset_path, AssetConverterContext* context)
{
  const std::string path = asset_path + "." + META_DATA_EXTENSION;
  if (!std::ifstream(path).is_open())
  {
    return new AssetMetaData(asset_path, context);
  }
  AssetMetaData* ret = CerealIO::Json::SafeImport<AssetMetaData>(path.c_str());
  if (!ret)
  {
    ret = new AssetMetaData(asset_path, context);
  }
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
AssetMetaData::AssetMetaData(const std::string& asset_path, AssetConverterContext* context)
  : path_(asset_path)
{
  this->unique_id_ = context->GetUniqueIdTable()->Publish(asset_path);
}

AssetMetaData::AssetMetaData()
{
}

// =================================================================
// Methods
// =================================================================
void AssetMetaData::Save()
{
  const std::string path = this->path_ + "." + META_DATA_EXTENSION;
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
  const std::string time_stamp = Util::File::GetTimeStamp(this->path_);
  const bool asset_changed = time_stamp != this->time_stamp_;
  if (asset_changed)
  {
    this->time_stamp_ = time_stamp;
  }
  return asset_changed;
}
