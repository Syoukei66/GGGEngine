#pragma once

#include <Entity/AssetImporter.h>
#include "CharacterModelAssetEntity.h"

class CharacterModelAssetImporter : public AssetImporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CharacterModelAssetImporter(const std::vector<std::string>& extensions);

  // =================================================================
  // Methods
  // =================================================================
protected:
  void* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override;

};
