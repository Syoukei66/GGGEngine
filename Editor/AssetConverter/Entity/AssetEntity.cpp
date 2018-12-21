#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>
#include <Util/Logger.h>
#include <Director.h>

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
void AssetEntity::CommitChanges()
{
  const T_UINT32 entity_count = (T_UINT32)this->sub_entities_.size();
  for (T_UINT32 i = 0; i < entity_count; ++i)
  {
    // AssetEntity‚ðƒŠƒtƒŒƒbƒVƒ…
    this->sub_entities_[i] = AssetConverterDirector::GetContext()->GetEntity(this->sub_entities_[i]->GetMetaData()->GetUniqueID());
    this->sub_entities_[i]->CommitChanges();
  }
  if (this->is_dirty_)
  {
    Logger::CommitAssetLog(this->meta_data_);
    this->RegisterAssetManager(this->meta_data_->GetUniqueID(), this->meta_data_->GetURI().GetExtension());
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
  for (const SharedRef<AssetEntity>& entity : this->sub_entities_)
  {
    entity->CheckAssetChanged(update_entities);
  }
}

bool AssetEntity::CheckSubAssetChanged()
{
  for (const SharedRef<AssetEntity>& entity : this->sub_entities_)
  {
    this->is_dirty_ |= entity->CheckSubAssetChanged();
  }
  return this->is_dirty_;
}

void AssetEntity::AddSubEntity(const SharedRef<AssetEntity>& entity)
{
  if (!entity)
  {
    return;
  }
  this->sub_entities_.push_back(entity);
  this->is_dirty_ = true;
}
