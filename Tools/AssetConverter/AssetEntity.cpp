#include "AssetEntity.h"
#include "AssetInfo.h"

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
