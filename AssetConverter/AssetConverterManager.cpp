#include "AssetConverterManager.h"
#include "../Core/CerealIO.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverterManager::AssetConverterManager(const Setting* setting)
{
  //Converter�̍쐬
  this->AddConverter(setting->raw_asset_converter_factory.Create());
}

AssetConverterManager::~AssetConverterManager()
{
  for (auto& pair : this->converters_map_)
  {
    for (IAssetConverter* converter : pair.second)
    {
      delete converter;
    }
  }
}

// =================================================================
// Methods
// =================================================================
bool AssetConverterManager::Fire(const std::function<bool(IAssetConverter*)>& func)
{
  for (auto& pair : this->converters_map_)
  {
    for (IAssetConverter* converter : pair.second)
    {
      if (func(converter))
      {
        return true;
      }
    }
  }
  return false;
}

void AssetConverterManager::VisitAll(const std::function<void(IAssetConverter*)>& func)
{
  for (auto& pair : this->converters_map_)
  {
    for (IAssetConverter* converter : pair.second)
    {
      func(converter);
    }
  }
}

void AssetConverterManager::VisitAll(const std::function<void(const IAssetConverter*)>& func) const
{
  for (auto& pair : this->converters_map_)
  {
    for (IAssetConverter* converter : pair.second)
    {
      func(converter);
    }
  }
}