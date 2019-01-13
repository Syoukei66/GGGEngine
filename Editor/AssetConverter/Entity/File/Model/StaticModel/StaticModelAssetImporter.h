#pragma once

#include <Entity/AssetImporter.h>
#include "StaticModelAssetEntity.h"

class StaticModelAssetImporter : public AssetImporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  StaticModelAssetImporter(const std::vector<std::string>& extensions);

  // =================================================================
  // Methods
  // =================================================================
protected:
  void* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override;

};
