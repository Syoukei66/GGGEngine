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
    IAssetLoader* asset = pair.second;
    if (asset->IsNeedUnload())
    {
      asset->Unload();
    }
    delete asset;
  }
  delete GetInstance()->unique_id_table_;
}

void AssetManager::Update()
{
  for (auto& pair : GetInstance()->assets_)
  {
    IAssetLoader* asset = pair.second;
    if (!asset->IsNeedUnload())
    {
      continue;
    }
    asset->Unload();
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
