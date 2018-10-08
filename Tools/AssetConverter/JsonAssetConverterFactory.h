#pragma once

#include "AssetEntity.h"
#include "RawAssetConverterFactory.h"

class JsonAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_JSON)
public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<JsonAssetEntity>("Json", "rcJsonData", "json");
  }
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  JsonAssetEntity(AssetInfo* info)
    : AssetEntity(info)
  {}
};
