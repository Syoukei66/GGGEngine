#include "AssetManager.h"
#include "AssetLoader.h"

#include <Asset/UniqueIdTable.h>

// =================================================================
// Methods
// =================================================================
void AssetManager::Init()
{
  Self().unique_id_table_ = CerealIO::Binary::Import<UniqueIdTable>(Directory::GetArchiveUniqueIdTablePath().c_str());
}

void AssetManager::Uninit()
{
  for (auto& pair : Self().loaders_)
  {
    pair.second->UnloadCache();
    delete pair.second;
  }
  delete Self().unique_id_table_;
}

void AssetManager::UnloadCaches()
{
  for (auto& pair : Self().loaders_)
  {
    pair.second->UnloadCache();
  }
}

// =================================================================
// Setter / Getter
// =================================================================
//size_t AssetManager::GetMemorySize() const
//{
//  return size_t();
//}
//
//size_t AssetManager::GetVideoMemorySize() const
//{
//  return size_t();
//}