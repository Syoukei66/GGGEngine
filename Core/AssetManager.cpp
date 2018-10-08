#include "AssetManager.h"
#include "AssetLoader.h"
#include "CerealIO.h"

#include <Core/Directory.h>

// =================================================================
// Methods
// =================================================================
void AssetManager::Init()
{
  GetInstance()->unique_id_table_ = CerealIO::Binary::Import<UniqueIdTable>(Directory::GetArchiveUniqueIdTablePath().c_str());
}

void AssetManager::Uninit()
{
  for (auto& pair : GetInstance()->assets_)
  {
    delete pair.second;
  }
  delete GetInstance()->unique_id_table_;
}

void AssetManager::UnloadCaches()
{
  for (auto& pair : GetInstance()->assets_)
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
