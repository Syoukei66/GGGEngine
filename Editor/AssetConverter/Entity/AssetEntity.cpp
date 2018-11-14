#include <Entity/AssetEntity.h>
#include <Entity/AssetInfo.h>
#include <Util/Logger.h>

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
  Logger::CommitAssetLog(this->info_);
  this->RegisterAssetManager(this->info_->GetUniqueID(), this->info_->GetURI().GetExtension());
}

void AssetEntity::CheckChanged(std::set<std::string>* sources)
{
  if (this->info_->GetMetaData()->UpdateTimeStamp())
  {
    sources->insert(this->info_->GetSourceURI().GetFullPath());
    this->info_->GetMetaData()->Save();
  }
  for (const SharedRef<AssetEntity>& entity : this->referenced_entities_)
  {
    entity->CheckChanged(sources);
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
