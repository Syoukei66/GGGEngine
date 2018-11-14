#include <Entity/AssetEntity.h>
#include <Entity/AssetInfo.h>
#include <Util/Logger.h>
#include <Director.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(AssetEntity, AssetInfo* info)
{
  this->info_ = info;
  return true;
}

GG_DESTRUCT_FUNC_IMPL(AssetEntity)
{
  delete this->info_;
  return true;
}

// =================================================================
// Methods
// =================================================================
void AssetEntity::CommitChanges()
{
  for (const SharedRef<AssetEntity>& entity : this->referenced_entities_)
  {
    entity->CommitChanges();
  }
  Logger::CommitAssetLog(this->info_);
  this->RegisterAssetManager(this->info_->GetUniqueID(), this->info_->GetURI().GetExtension());
}

void AssetEntity::CheckChanged(std::set<SharedRef<AssetEntity>>* update_entities)
{
  if (this->info_->GetMetaData()->UpdateTimeStamp())
  {
    this->info_->GetMetaData()->Save();
    update_entities->insert(AssetConverterDirector::GetContext()->GetEntity(this->info_->GetSourceURI()));
  }
  for (const SharedRef<AssetEntity>& entity : this->referenced_entities_)
  {
    entity->CheckChanged(update_entities);
  }
}

void AssetEntity::AddReferencedEntity(const SharedRef<AssetEntity>& entity)
{
  if (!entity)
  {
    return;
  }
  this->referenced_entities_.push_back(entity);
}
