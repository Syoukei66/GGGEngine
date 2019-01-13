#pragma once

#include <Entity/AssetImporter.h>
#include "ShaderAssetEntity.h"

class ShaderAssetImporter : public AssetImporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ShaderAssetImporter(const std::vector<std::string>& extensions);

  // =================================================================
  // Methods
  // =================================================================
protected:
  void* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override;

};
