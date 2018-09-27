#pragma once

#include "AssetEntity.h"
#include "RawAssetConverterFactory.h"

class CsvAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_CSV)
public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<CsvAssetEntity>("CSV", "CsvAsset", "csv");
  }
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CsvAssetEntity(AssetInfo* info)
    : AssetEntity(info)
  {}
};
