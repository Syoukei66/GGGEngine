#include "AssetManager.h"
#include "AssetLoader.h"

#include <Core/Application/Asset/UniqueIdTable.h>

// =================================================================
// Methods
// =================================================================
void AssetManager::Init()
{
  AssetManager* self = &Self();
  self->unique_id_table_ = CerealIO::Binary::Import<UniqueIdTable>(Directory::GetArchiveUniqueIdTablePath().c_str());
}

void AssetManager::Init(UniqueIdTable* table)
{
  AssetManager* self = &Self();
  self->unique_id_table_ = table;
}

void AssetManager::Uninit()
{
  AssetManager* self = &Self();
  for (auto& pair : self->loaders_)
  {
    pair.second->UnloadCache();
    delete pair.second;
  }
  delete self->unique_id_table_;
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
