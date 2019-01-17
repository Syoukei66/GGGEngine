#include "AssetConverterManager.h"
#include <Entity/AssetEntity.h>

#include <Converter/AssetConverter.h>

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