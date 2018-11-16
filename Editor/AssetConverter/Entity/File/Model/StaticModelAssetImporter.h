#pragma once

#include <Entity/AssetImporter.h>
#include "StaticModelAssetEntity.h"

class StaticModelAssetImporter : public AssetImporter<StaticModelAssetEntity>
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
  SharedRef<StaticModelAssetEntity> ImportProcess(AssetInfo* info, AssetConverterContext* context) override;

};
