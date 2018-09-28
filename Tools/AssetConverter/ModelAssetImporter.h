#pragma once

#include "AssetImporter.h"
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
  ModelAssetEntity* ImportProcess(AssetInfo* info, AssetConverterContext* context) override;

};
