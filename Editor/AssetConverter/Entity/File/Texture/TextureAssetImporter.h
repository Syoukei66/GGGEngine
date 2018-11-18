#pragma once

#include <Entity/AssetImporter.h>
#include "TextureAssetEntity.h"

class TextureAssetImporter : public AssetImporter<TextureAssetEntity>
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
  SharedRef<TextureAssetEntity> ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override;

};
