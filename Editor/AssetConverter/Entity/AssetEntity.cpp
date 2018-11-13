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
