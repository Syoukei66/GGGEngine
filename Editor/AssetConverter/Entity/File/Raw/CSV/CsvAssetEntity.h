#pragma once

#include <Entity/File/Raw/RawAssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class CsvAssetEntity : public RawAssetEntity<rcCsvData>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_CSV);
  GG_OBJECT(CsvAssetEntity);
  GG_CREATE_FUNC_1(CsvAssetEntity, AssetMetaData*)
  {
    return AssetEntity::Init(arg0);
  }

public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<CsvAssetEntity>("CSV", "rcCsvData", "csv");
  }

};
