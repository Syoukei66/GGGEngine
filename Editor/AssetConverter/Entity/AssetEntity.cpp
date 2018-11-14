#include <Entity/AssetEntity.h>
#include <Entity/AssetInfo.h>
#include <Util/Logger.h>

// =================================================================
// Constructor / Destructor
// =================================================================
AssetEntity::AssetEntity(AssetInfo* info)
  : info_(info)
{
}

AssetEntity::~AssetEntity()
{
  delete this->info_;
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
  for (AssetEntity* entity : this->referenced_entities_)
  {
    entity->CheckChanged(sources);
  }
}

void AssetEntity::AddReferencedEntity(AssetEntity* entity)
{
  if (!entity)
  {
    return;
  }
  this->referenced_entities_.push_back(entity);
}
