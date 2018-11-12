#include "AssetConverterManager.h"
#include <Entity/AssetEntity.h>

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverterManager::AssetConverterManager()
  :converter_map_()
{
}

AssetConverterManager::~AssetConverterManager()
{
  for (auto& pair : this->converter_map_)
  {
    delete pair.second;
  }
}

// =================================================================
// Methods
// =================================================================
bool AssetConverterManager::Fire(const std::function<bool(IAssetConverter*)>& func)
{
  for (auto& pair : this->converter_map_)
  {
    if (func(pair.second))
    {
      return true;
    }
  }
  return false;
}

void AssetConverterManager::VisitAll(const std::function<void(IAssetConverter*)>& func)
{
  for (auto& pair : this->converter_map_)
  {
    func(pair.second);
  }
}

void AssetConverterManager::VisitAll(const std::function<void(const IAssetConverter*)>& func) const
{
  for (auto& pair : this->converter_map_)
  {
    func(pair.second);
  }
}

void AssetConverterManager::VisitAllEntity(const std::function<void(AssetEntity*)>& func)
{
  for (auto& pair : this->converter_map_)
  {
    pair.second->VisitAllEntity(func);
  }
}
