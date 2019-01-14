#pragma once

#include <Entity/AssetImporter.h>

class RawAssetImporter : public AssetImporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RawAssetImporter(const std::vector<std::string>& extensions)
    : AssetImporter(extensions)
  {
  }

  // =================================================================
  // Methods
  // =================================================================
protected:
  void* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override
  {
    return nullptr;
  }

};
