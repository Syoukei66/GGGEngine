#pragma once

#include <Entity/File/Raw/RawAssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class CsvAssetEntity : public RawAssetEntity<rcCsvData>
{
  ENTITY_ID(ID_CSV);

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
    : RawAssetEntity(info)
  {}
};
