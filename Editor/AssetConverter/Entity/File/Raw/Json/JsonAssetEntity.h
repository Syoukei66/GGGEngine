#pragma once

#include <Entity/File/Raw/RawAssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class JsonAssetEntity : public RawAssetEntity<rcJsonData>
{
  ENTITY_ID(ID_JSON);

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
    : RawAssetEntity(info)
  {}
};
