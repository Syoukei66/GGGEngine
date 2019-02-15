#include "AssetMetaData.h"

#include <Util/FileUtil.h>
#include <Constants/Extensions.h>
#include <Converter/AssetConverter.h>
#include <Converter/AssetConverterContext.h>
#include <Director.h>
#include <ctime>

#include "ConverterSettingPolymorphicRelations.h"

// =================================================================
// Factory Method
// =================================================================
AssetMetaData* AssetMetaData::Create(const URI& uri, AssetConverterContext* context)
{
  return AssetMetaData::Create(uri, context->PublishUniqueID(uri), context);
}

AssetMetaData* AssetMetaData::Create(const URI& uri, AssetConverter* converter, AssetConverterContext* context)
{
  AssetMetaData* ret = AssetMetaData::Create(uri, context->PublishUniqueID(uri), context);
  ret->SetConverterSetting(converter->CreateSetting());
  return ret;
}

AssetMetaData* AssetMetaData::Create(const URI& uri, T_UINT32 source_unique_id, AssetConverterContext* context)
{
  if (AssetConverterDirector::IsUniqueIdTableLoadFailed())
  {
    AssetMetaData* ret = new AssetMetaData(uri, source_unique_id, context);
    ret->Save();
    return ret;
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
  , time_stamp_()
  , last_import_time_stamp_()
  , unique_id_(context->PublishUniqueID(uri))
  , source_unique_id_(source_unique_id)
  , converter_setting_()
{}

// =================================================================
// Methods
// =================================================================
void AssetMetaData::Save()
{
  const std::string path = FileUtil::CreateInputPath(this->uri_.GetFullPath() + "." + Extensions::META);
  //this->UpdateTimeStamp();
  CerealIO::Json::Export(path.c_str(), this);
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

void AssetMetaData::UpdateLastImportTimeStamp()
{
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);
  std::string ret = std::string();
  ret.append(std::to_string(now->tm_year));
  ret.append("/");
  ret.append(std::to_string(now->tm_mon));
  ret.append("/");
  ret.append(std::to_string(now->tm_mday));
  ret.append(" ");
  ret.append(std::to_string(now->tm_hour));
  ret.append(":");
  ret.append(std::to_string(now->tm_min));
  ret.append(":");
  ret.append(std::to_string(now->tm_sec));
  this->last_import_time_stamp_ = ret;
}
