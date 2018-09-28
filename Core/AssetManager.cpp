#include "AssetManager.h"
#include "Asset.h"
#include "CerealIO.h"

// =================================================================
// Methods
// =================================================================
void AssetManager::Init()
{
  this->default_uids_ = DefaultUniqueID::Deserialize("DefaultUniqueID");
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
