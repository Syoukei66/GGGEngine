#pragma once

#include <Entity/AssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class CsvAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_CSV)
public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<CsvAssetEntity>("CSV", "rcCsvData", "csv");
  }
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CsvAssetEntity(AssetInfo* info)
    : AssetEntity(info)
  {}
};
