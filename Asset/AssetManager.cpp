#include "AssetManager.h"
#include "AssetLoader.h"

// =================================================================
// Methods
// =================================================================
void AssetManager::Init()
{
  Instance().unique_id_table_ = CerealIO::Binary::Import<UniqueIdTable>(Directory::GetArchiveUniqueIdTablePath().c_str());
}

void AssetManager::Uninit()
{
  for (auto& pair : Instance().loaders_)
  {
    pair.second->UnloadCache();
    delete pair.second;
  }
  delete Instance().unique_id_table_;
}

void AssetManager::UnloadCaches()
{
  for (auto& pair : Instance().loaders_)
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
