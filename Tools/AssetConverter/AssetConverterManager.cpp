#include "AssetConverterManager.h"
#include <Core/CerealIO.h>

#include "CsvAssetConverterFactory.h"
#include "JsonAssetConverterFactory.h"
#include "ShaderAssetConverterFactory.h"
#include "SoundAssetConverterFactory.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverterManager::AssetConverterManager(const Setting* setting)
{
  //Converter�̍쐬
  this->AddConverter(setting->texture_asset_converter_factory.Create());
  this->AddConverter(setting->model_asset_converter_factory.Create());
  this->AddConverter(setting->model_mesh_asset_converter_factory.Create());
  this->AddConverter(setting->model_material_asset_converter_factory.Create());
  this->AddConverter(CsvAssetEntity::CreateConverter());
  this->AddConverter(JsonAssetEntity::CreateConverter());
  this->AddConverter(ShaderAssetEntity::CreateConverter());
  this->AddConverter(SoundAssetEntity::CreateConverter());
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