#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>
#include <Converter/AssetConverter.h>
#include <Converter/AssetConverterContext.h>
#include <Util/Logger.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(AssetEntity, AssetMetaData* meta)
{
  this->meta_data_ = meta;
  this->is_need_commit_ = true;
  return true;
}

GG_INIT_FUNC_IMPL_2(AssetEntity, AssetMetaData* meta, IAssetDataContainer* data)
{
  this->meta_data_ = meta;
  this->SetData(data);
  return true;
}

GG_DESTRUCT_FUNC_IMPL(AssetEntity)
{
  delete this->meta_data_;
  delete this->data_;
  return true;
}

// =================================================================
// Methods
// =================================================================
bool AssetEntity::Load(AssetConverterContext* context)
{
  std::set<SharedRef<AssetEntity>> changed_entities_ = std::set<SharedRef<AssetEntity>>();

  // ConverterSettingが無ければロード処理は行わない
  if (!this->meta_data_->GetConverterSetting())
  {
    return false;
  }

  // アセットに変更があるか検出
  this->CheckAssetChanged(context, &changed_entities_);
  if (changed_entities_.size() > 0)
  {
    // 変更があったアセットをインポートし直す
    for (const SharedRef<AssetEntity>& entity : changed_entities_)
    {
      entity->Import(context);
    }
  }    
  // サブアセットの変更を検出
  if (this->CheckSubAssetChanged(context))
  {
    // AssetEntityをリフレッシュし、シーンのリロードを行う
    this->CommitChanges(context);
    return true;
  }
  return false;
}

void AssetEntity::Export(AssetConverterContext* context)
{
  AssetConverter* converter = this->GetConverter(context);
  //TODO: 中間データが最新のものかチェックし、最新でなかったらインポートする処理を書く
  converter->ExportImmediately(SharedRef<AssetEntity>(this), context);
}

void AssetEntity::ClearCache()
{
  this->SetData(nullptr);
}

void AssetEntity::Import(AssetConverterContext* context)
{
  Logger::ImportAssetLog(this->meta_data_->GetURI());
  AssetConverter* converter = this->GetConverter(context);
  this->SetData(converter->ImportImmediately(SharedRef<AssetEntity>(this), context));
  this->is_need_commit_ = true;
}

bool AssetEntity::ImportFromCache(AssetConverterContext* context)
{
  Logger::ImportFromCacheAssetLog(this->meta_data_->GetURI());
  AssetConverter* converter = this->GetConverter(context);
  IAssetDataContainer* data = converter->ImportFromCache(SharedRef<AssetEntity>(this), context);
  if (!data)
  {
    return false;
  }
  this->SetData(data);
  this->is_need_commit_ = true;
  return true;
}

void AssetEntity::CommitChanges(AssetConverterContext* context)
{
  const std::unique_ptr<ConverterSetting>& setting = this->meta_data_->GetConverterSetting();
  const std::unordered_set<T_UINT32>& sub_asset_uids = setting->GetSubAssetUniqueIds();

  // このコミットでのサブアセットのインポートタイムスタンプを取得
  this->sub_asset_import_time_stamps_.clear();
  for (T_UINT32 uid : sub_asset_uids)
  {
    const SharedRef<AssetEntity>& entity = context->GetEntity(uid);
    entity->CommitChanges(context);
    this->sub_asset_import_time_stamps_[uid] = entity->GetMetaData()->GetLastImportTimeStamp();
  }
  if (this->is_need_commit_)
  {
    Logger::CommitAssetLog(this->meta_data_);
    AssetConverter* converter = context->GetConverter(setting->GetConverterID());
    converter->RegisterAssetManager(SharedRef<AssetEntity>(this));
    this->is_need_commit_ = false;
  }
}

void AssetEntity::CheckAssetChanged(AssetConverterContext* context, std::set<SharedRef<AssetEntity>>* update_entities)
{
  bool dirty_self = false;

  // タイムスタンプが更新されていたら
  if (this->meta_data_->UpdateTimeStamp())
  {
    // メタデータを保存し、ダーティフラグを立てる
    this->meta_data_->Save();
    dirty_self = true;
  }
  
  // ConverterSettingが無ければ何も行わない
  if (!this->meta_data_->GetConverterSetting())
  {
    return;
  }

  // ConverterSettingに変更があったらダーティフラグを立てる
  if (this->meta_data_->GetConverterSetting()->IsDirty())
  {
    dirty_self = true;
  }

  // SourceAssetも同様に調査する
  const SharedRef<AssetEntity>& source = context->GetEntity(this->meta_data_->GetSourceUniqueId());
  bool dirty_source = false;

  // タイムスタンプが更新されていたら
  if (source->GetMetaData()->UpdateTimeStamp())
  {
    // メタデータを保存し、ダーティフラグを立てる
    source->GetMetaData()->Save();
    dirty_source = true;
  }
  
  // ConverterSettingに変更があったらダーティフラグを立てる
  if (source->GetMetaData()->GetConverterSetting()->IsDirty())
  {
    dirty_source = true;
  }

  // 中間データが存在しておらず、
  // ダーティフラグが立っていなければキャッシュを拾ってくる
  if (!this->data_ && !dirty_self && !dirty_source)
  {
    // キャッシュからの読み込みも失敗したならダーティフラグを立てる
    if (!this->ImportFromCache(context))
    {
      dirty_self = true;
    }
  }
  
  // ダーティフラグが立っていたらupdate_entitiesにUniqueIdを追加する
  if (dirty_self)
  {
    update_entities->insert(SharedRef<AssetEntity>(this));
  }

  // ダーティフラグが立っていたらupdate_entitiesにソースUniqueIdを追加する
  if (dirty_source)
  {
    update_entities->insert(source);
  }

  // まだチェックしていないサブアセットがあれば
  const std::unordered_set<T_UINT32>& sub_asset_uids = this->meta_data_->GetConverterSetting()->GetSubAssetUniqueIds();
  for (T_UINT32 uid : sub_asset_uids)
  {
    context->GetEntity(uid)->CheckAssetChanged(context, update_entities);
  }
}

bool AssetEntity::CheckSubAssetChanged(AssetConverterContext* context)
{
  const std::unordered_set<T_UINT32>& sub_asset_uids = this->meta_data_->GetConverterSetting()->GetSubAssetUniqueIds();
  for (T_UINT32 uid : sub_asset_uids)
  {
    const SharedRef<AssetEntity>& entity = context->GetEntity(uid);
    // (1)
    // 前回のコミット時とサブアセットのインポートタイムスタンプに
    // 違いがあればコミットをしなおす必要がある。
    if (!this->is_need_commit_)
    {
      // インポートタイムスタンプが記録されているか調べる
      const auto& itr = this->sub_asset_import_time_stamps_.find(uid);
      if (itr == this->sub_asset_import_time_stamps_.end())
      {
        // 記録されていなければコミットが必要
        this->is_need_commit_ = true;
      }
      else
      {
        // 記録されているが違いがあった場合もコミットが必要
        if (itr->second != entity->GetMetaData()->GetLastImportTimeStamp())
        {
          this->is_need_commit_ = true;
        }
      }
    }
    this->sub_asset_import_time_stamps_[uid] = entity->GetMetaData()->GetLastImportTimeStamp();

    // (2)
    // サブアセットにコミットがあれば自身もコミットする必要がある。
    this->is_need_commit_ |= context->GetEntity(uid)->CheckSubAssetChanged(context);
  }

  // 呼び出し主に自身のコミットの有無を伝える
  return this->is_need_commit_;
}

// =================================================================
// Getter / Setter
// =================================================================
void AssetEntity::SetData(IAssetDataContainer* data)
{
  if (this->data_ == data)
  {
    return;
  }
  if (this->data_)
  {
    delete this->data_;
  }
  this->data_ = data;
  if (!this->data_)
  {
    return;
  }
  this->data_->SaveCache(this->meta_data_->GetURI());
  this->meta_data_->UpdateLastImportTimeStamp();
  this->is_need_commit_ = true;
}

AssetConverter* AssetEntity::GetConverter(AssetConverterContext* context) const
{
  const std::unique_ptr<ConverterSetting>& setting = this->meta_data_->GetConverterSetting();
  if (!setting)
  {
    return nullptr;
  }
  return context->GetConverter(setting->GetConverterID());
}
