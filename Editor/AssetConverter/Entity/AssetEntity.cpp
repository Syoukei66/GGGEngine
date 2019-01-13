#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>
#include <Util/Logger.h>
#include <Director.h>

#include <Entity/AssetImporter.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(AssetEntity, AssetMetaData* meta)
{
  this->meta_data_ = meta;
  this->is_dirty_ = true;
  return true;
}

GG_DESTRUCT_FUNC_IMPL(AssetEntity)
{
  delete this->meta_data_;
  return true;
}

// =================================================================
// Methods
// =================================================================
bool AssetEntity::Load(AssetConverterContext* context)
{
  std::set<SharedRef<AssetEntity>> changed_entities_ = std::set<SharedRef<AssetEntity>>();

  // アセットに変更があるか検出
  this->CheckAssetChanged(&changed_entities_);
  if (changed_entities_.size() > 0)
  {
    // 変更があったアセットをインポートし直す
    for (const SharedRef<AssetEntity>& entity : changed_entities_)
    {
      entity->Import(context);
    }
    // サブアセットの変更を検出
    this->CheckSubAssetChanged();

    // AssetEntityをリフレッシュし、シーンのリロードを行う
    this->CommitChanges(context);
    return true;
  }
  return false;
}

void AssetEntity::Export(AssetConverterContext* context)
{
  AssetConverter* converter = context->GetConverter(this->meta_data_->GetConverterSetting()->GetConverterID());
  //TODO: 中間データが最新のものかチェックし、最新でなかったらインポートする処理を書く
  converter->ExportImmediately(this->meta_data_, context);
}

void AssetEntity::Import(AssetConverterContext* context)
{
  const std::unique_ptr<ImporterSetting>& setting = this->meta_data_->GetConverterSetting();
  AssetConverter* converter = context->GetConverter(setting->GetConverterID());
  if (this->data_)
  {
    delete this->data_;
  }
  this->data_ = converter->ImportImmediately(this->meta_data_, context);
}

void AssetEntity::CommitChanges(AssetConverterContext* context)
{
  const std::unique_ptr<ImporterSetting>& setting = this->meta_data_->GetConverterSetting();
  const std::unordered_set<T_UINT32>& sub_asset_uids = setting->GetSubAssetUniqueIds();
  for (T_UINT32 uid : sub_asset_uids)
  {
    // AssetEntityをリフレッシュ
    AssetConverterDirector::GetContext()->GetEntity(uid)->CommitChanges(context);
  }
  if (this->is_dirty_)
  {
    Logger::CommitAssetLog(this->meta_data_);
    AssetConverter* converter = context->GetConverter(setting->GetConverterID());
    converter->RegisterAssetManager(this->meta_data_->GetUniqueID(), this->meta_data_->GetURI().GetExtension(), this->data_);
    setting->IsMidFileDirty();
    this->is_dirty_ = false;
  }
}

void AssetEntity::CheckAssetChanged(std::set<SharedRef<AssetEntity>>* update_entities)
{
  if (this->meta_data_->UpdateTimeStamp())
  {
    this->meta_data_->Save();
    update_entities->insert(AssetConverterDirector::GetContext()->GetEntity(this->meta_data_->GetSourceUniqueId()));
    this->is_dirty_ = true;
  }
  const std::unordered_set<T_UINT32>& sub_asset_uids = this->meta_data_->GetConverterSetting()->GetSubAssetUniqueIds();
  for (T_UINT32 uid : sub_asset_uids)
  {
    AssetConverterDirector::GetContext()->GetEntity(uid)->CheckAssetChanged(update_entities);
  }
}

bool AssetEntity::CheckSubAssetChanged()
{
  const std::unordered_set<T_UINT32>& sub_asset_uids = this->meta_data_->GetConverterSetting()->GetSubAssetUniqueIds();
  for (T_UINT32 uid : sub_asset_uids)
  {
    this->is_dirty_ |= AssetConverterDirector::GetContext()->GetEntity(uid)->CheckSubAssetChanged();
  }
  return this->is_dirty_;
}