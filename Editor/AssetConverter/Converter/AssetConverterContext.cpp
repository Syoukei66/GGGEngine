#include "AssetConverterContext.h"
#include "AssetConverter.h"
#include <Core/Application/Asset/UniqueIdTable.h>
#include <Constants/Extensions.h>
#include <Util/Logger.h>

AssetConverterContext::AssetConverterContext(UniqueIdTable* unique_id_table)
  : unique_id_table_(unique_id_table)
{
}

AssetConverterContext::~AssetConverterContext()
{
  for (const auto& pair : this->converter_map_)
  {
    delete pair.second;
  }
  for (const auto& pair : this->default_asset_converter_map_)
  {
    delete pair.second;
  }
}

void AssetConverterContext::Fetch()
{
  // (1)
  // URIからUniqueIdを作成、
  // uniqueIdがasset_entities_に登録されていないファイルを見つけ、
  // AssetEntityが存在しないファイルのURIリストに格納
  std::vector<URI> unknown_files = std::vector<URI>();
 
  FileUtil::CrawlInputDirectory([&](const URI& uri)
  {
    // メタデータはスキップ
    if (uri.GetExtension() == Extensions::META)
    {
      return;
    }
    // AssetEntityが存在していないファイルをunknown_filesに追加
    const T_UINT32 uid = this->PublishUniqueID(uri.GetFullPath());
    if (this->asset_entities_.find(uid) == this->asset_entities_.end())
    {
      unknown_files.emplace_back(uri);
    }
  });

  // (2)
  // AssetEntityが存在しないファイルのURIリストから
  // MetaDataがあるかどうかを探す
  for (const URI& uri : unknown_files)
  {
    if (FileUtil::IsFileExist((uri.GetFullPath() + "." + Extensions::META).c_str()))
    {
      //TODO: MetaDataがあるが、MetaData内のURIが実際のURIと対応していないファイルについての処理を記述する。
    }
    // AssetEntity、MetaDataを作成
    const T_UINT32 uid = this->PublishUniqueID(uri.GetFullPath());
    this->AddEntity(AssetEntity::Create(AssetMetaData::Create(uri, this)));
  }

  // UniqueIdTableを保存する
  CerealIO::Json::Export(FileUtil::GetMidDataUniqueIdTablePath().c_str(), this->unique_id_table_);
}

void AssetConverterContext::VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func)
{
  for (const auto& pair : this->asset_entities_)
  {
    func(pair.second);
  }
}

SharedRef<AssetEntity> AssetConverterContext::AddEntity(const SharedRef<AssetEntity>& entity)
{
  AssetMetaData* meta_data = entity->GetMetaData();

  if (!entity)
  {
    Logger::ConvertFaildLog(meta_data);
    return nullptr;
  }

  const URI& uri = meta_data->GetURI();
  // ConverterSettingが無ければデフォルトのConverterSettingを設定する
  if (!meta_data->GetConverterSetting())
  {
    // デフォルトアセットならデフォルトアセット用のデフォルトのConverterSettingを設定する
    if (this->default_asset_unique_id_.find(uri.GetFullPath()) != this->default_asset_unique_id_.end())
    {
      for (const auto& pair : this->default_asset_converter_map_)
      {
        if (pair.second->IsTarget(uri))
        {
          meta_data->SetConverterSetting(pair.second->CreateSetting());
          break;
        }
      }
    }
    else
    {
      for (const auto& pair : this->converter_map_)
      {
        if (pair.second->IsTarget(uri))
        {
          meta_data->SetConverterSetting(pair.second->CreateSetting());
          break;
        }
      }
    }
  }

  this->asset_entities_[entity->GetMetaData()->GetUniqueID()] = entity;
  return entity;
}

SharedRef<AssetEntity> AssetConverterContext::GetEntity(const URI& uri)
{
  return this->asset_entities_[this->GetUniqueID(uri.GetFullPath())];
}

SharedRef<AssetEntity> AssetConverterContext::GetEntity(T_UINT32 unique_id)
{
  if (unique_id > DefaultUniqueID::DEFAULT_UID_BEGIN)
  {
    unique_id = this->unique_id_table_->GetDefaultAssetUniqueID(unique_id);
  }
  return this->asset_entities_[unique_id];
}

T_UINT32 AssetConverterContext::PublishUniqueID(const URI& uri)
{
  return this->unique_id_table_->Publish(FileUtil::CreateRuntimeAssetPath(uri));
}

T_UINT32 AssetConverterContext::GetUniqueID(const URI& uri) const
{
  return this->unique_id_table_->GetID(FileUtil::CreateRuntimeAssetPath(uri));
}

void AssetConverterContext::RegisterDefaultUniqueID(T_UINT32 default_uid, const URI& uri)
{
  this->unique_id_table_->RegisterDefaultAssetUniqueID(default_uid, FileUtil::CreateRuntimeAssetPath(uri));
  this->default_asset_uri_[default_uid] = uri;
  this->default_asset_unique_id_[uri.GetFullPath()] = this->unique_id_table_->GetDefaultAssetUniqueID(default_uid);
}

AssetConverter* AssetConverterContext::AddConverter(AssetConverter* converter)
{
  this->converter_map_[converter->GetId()] = converter;
  return converter;
}

AssetConverter* AssetConverterContext::AddDefaultAssetConverter(AssetConverter* converter)
{
  this->default_asset_converter_map_[converter->GetId()] = converter;
  return converter;
}

AssetConverter* AssetConverterContext::GetConverter(const std::string& id)
{
  const auto& itr = this->converter_map_.find(id);
  if (itr != this->converter_map_.end())
  {
    return this->converter_map_[id];
  }
  return this->default_asset_converter_map_[id];
}

const AssetConverter* AssetConverterContext::GetConverter(const std::string& id) const
{
  const auto& itr = this->converter_map_.find(id);
  if (itr != this->converter_map_.end())
  {
    return this->converter_map_.at(id);
  }
  return this->default_asset_converter_map_.at(id);
}
