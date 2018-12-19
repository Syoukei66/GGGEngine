#pragma once

#include <Entity/AssetImporter.h>
#include "ShaderAssetEntity.h"

class ShaderAssetImporter : public AssetImporter<ShaderAssetEntity>
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
  SharedRef<ShaderAssetEntity> ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override;

};
