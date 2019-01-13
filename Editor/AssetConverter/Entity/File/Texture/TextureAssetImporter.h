#pragma once

#include <Entity/AssetImporter.h>
#include "TextureAssetEntity.h"

class TextureAssetImporter : public AssetImporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureAssetImporter(const std::vector<std::string>& extensions);

  // =================================================================
  // Methods
  // =================================================================
protected:
  void* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override;

};
