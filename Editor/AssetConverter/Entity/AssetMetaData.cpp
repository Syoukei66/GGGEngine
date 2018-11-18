#include "AssetMetaData.h"

#include <Util/FileUtil.h>
#include "Director.h"
#include <Constants/Extensions.h>
#include <Director.h>

// =================================================================
// Factory Method
// =================================================================
AssetMetaData* AssetMetaData::Create(const URI& uri, AssetConverterContext* context)
{
  return AssetMetaData::Create(uri, context->PublishUniqueID(uri), context);
}

AssetMetaData* AssetMetaData::Create(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context)
{
  if (AssetConverterDirector::IsUniqueIdTableLoadFailed())
  {
    return new AssetMetaData(uri, source_unique_id, context);
  }
  const std::string path = FileUtil::CreateInputPath(uri.GetFullPath() + "." + Extensions::META);
  if (!std::ifstream(path).is_open())
  {
    return new AssetMetaData(uri, source_unique_id, context);
  }
  AssetMetaData* ret = CerealIO::Json::SafeImport<AssetMetaData>(path.c_str());
  GG_ASSERT(!ret || ret->unique_id_ == context->GetUniqueID(uri), "メタデータとUniqueIdTableに不整合が見つかりました");
  if (!ret)
  { 
    // メタデータの読み込みに失敗したらメタデータを作成
    ret = new AssetMetaData(uri, source_unique_id, context);
  }
  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
AssetMetaData::AssetMetaData(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context)
  : uri_(uri)
  , source_unique_id_(source_unique_id)
{
  this->unique_id_ = context->PublishUniqueID(uri);
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
  AssetMetaData* ret = new AssetMetaData(child_path, this->source_unique_id_, context);
  this->related_unique_ids_.emplace(ret->unique_id_);
  return ret;
}

void AssetMetaData::ResetTimeStamp()
{
  this->time_stamp_ = "";
}

bool AssetMetaData::UpdateTimeStamp()
{
  const std::string time_stamp = FileUtil::GetTimeStamp(FileUtil::CreateInputPath(AssetConverterDirector::GetUniqueIdTable()->GetPath(this->source_unique_id_)));
  const bool asset_changed = time_stamp != this->time_stamp_;
  if (asset_changed)
  {
    this->time_stamp_ = time_stamp;
  }
  return asset_changed;
}
