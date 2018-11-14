#pragma once

#include <Entity/AssetImporter.h>
#include "ModelAssetEntity.h"

class ModelAssetImporter : public AssetImporter<ModelAssetEntity>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelAssetImporter(const std::vector<std::string>& extensions);

  // =================================================================
  // Methods
  // =================================================================
protected:
  SharedRef<ModelAssetEntity> ImportProcess(AssetInfo* info, AssetConverterContext* context) override;

};
