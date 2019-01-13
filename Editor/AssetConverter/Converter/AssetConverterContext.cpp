#include "AssetConverterContext.h"
#include "AssetConverterManager.h"
#include "AssetConverter.h"
#include <Core/Application/Asset/UniqueIdTable.h>
#include <Constants/Extensions.h>

AssetConverterContext::AssetConverterContext(UniqueIdTable* unique_id_table, AssetConverterManager* converter_manager)
  : unique_id_table_(unique_id_table)
  , converter_manager_(converter_manager)
{
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
    const T_UINT32 uid = this->unique_id_table_->Publish(uri.GetFullPath());
    if (this->asset_entities_.find(uid) == this->asset_entities_.end())
    {
      unknown_files.emplace_back(uri);
    }
  });

  // (2)
  // AssetEntityが存在しないファイルのURIリストから
  // MetaDataがあるかどうかを探す

  // UniqueIdTableを保存する
  CerealIO::Json::Export(FileUtil::GetMidDataUniqueIdTablePath().c_str(), self->unique_id_table_);

  self->context_->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    entity->GetMetaData()->Save();
  });

  self->converter_manager_->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    entity->CommitChanges();
  });
}

bool AssetConverterContext::Reserve(const URI& uri)
{
  //Infoが生成されるまでConverterを走査
  return this->converter_manager_->Fire([&](AssetConverter* converter)
  {
    return converter->Reserve(uri, this);
  });
}

bool AssetConverterContext::Reserve(const URI& uri, T_UINT32 source_unique_id)
{
  //Infoが生成されるまでConverterを走査
  return this->converter_manager_->Fire([&](AssetConverter* converter)
  {
    return converter->Reserve(uri, source_unique_id, this);
  });
}

void AssetConverterContext::VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func)
{
  this->converter_manager_->VisitAllEntity(func);
}

SharedRef<AssetEntity> AssetConverterContext::AddEntity(const SharedRef<AssetEntity>& entity)
{
  if (!entity)
  {
    Logger::ConvertFaildLog(entity->GetMetaData());
    return nullptr;
  }
  this->converter_manager_->VisitAll<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    converter->AddEntity(entity);
  });
  return entity;
}

template<class Entity_>
SharedRef<Entity_> AssetConverterContext::GetEntity(const URI& uri)
{
  return this->converter_manager_->Find<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->GetEntity(uri, this);
  });
}

SharedRef<AssetEntity> AssetConverterContext::GetEntity(const URI& uri)
{
  return this->converter_manager_->FindAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    return entity->GetMetaData()->GetURI() == uri;
  });
}

template<class Entity_>
SharedRef<Entity_> AssetConverterContext::GetEntity(T_UINT32 unique_id)
{
  if (unique_id > DefaultUniqueID::DEFAULT_UID_BEGIN)
  {
    unique_id = this->unique_id_table_->GetDefaultAssetUniqueID(unique_id);
  }
  return this->converter_manager_->Find<Entity_>([&](AssetConverter<Entity_>* converter)
  {
    return converter->GetEntity(unique_id);
  });
}

SharedRef<AssetEntity> AssetConverterContext::GetEntity(T_UINT32 unique_id)
{
  if (unique_id > DefaultUniqueID::DEFAULT_UID_BEGIN)
  {
    unique_id = this->unique_id_table_->GetDefaultAssetUniqueID(unique_id);
  }
  return this->converter_manager_->FindAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    return entity->GetMetaData()->GetUniqueID() == unique_id;
  });
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
}
