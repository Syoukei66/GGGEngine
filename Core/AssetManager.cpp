#include "AssetManager.h"
#include "Asset.h"
#include "CerealIO.h"

// =================================================================
// Methods
// =================================================================
void AssetManager::Init()
{
  //if (this->unique_id_table_)
  //{
  //  delete this->unique_id_table_;
  //}
  //this->unique_id_table_ = CerealIO::Binary::Import<UniqueIdTable>("UniqueIdTable");
}

void AssetManager::Uninit()
{
  for (auto& pair : this->assets_)
  {
    IAsset* asset = pair.second;
    if (asset->IsNeedUnload())
    {
      asset->Unload();
    }
    delete asset;
  }
  //delete this->unique_id_table_;
  //this->unique_id_table_ = nullptr;
}

void AssetManager::Update()
{
  for (auto& pair : this->assets_)
  {
    IAsset* asset = pair.second;
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
