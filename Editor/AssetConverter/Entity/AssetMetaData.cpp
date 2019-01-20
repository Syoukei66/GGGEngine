#include "AssetMetaData.h"

#include <Util/FileUtil.h>
#include <Constants/Extensions.h>
#include <Converter/AssetConverter.h>
#include <Converter/AssetConverterContext.h>

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
