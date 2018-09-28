#pragma once

#include "AssetImporter.h"
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
  TextureAssetEntity* ImportProcess(AssetInfo* info, AssetConverterContext* context) override;

};
