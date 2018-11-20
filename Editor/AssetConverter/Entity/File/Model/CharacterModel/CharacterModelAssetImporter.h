#pragma once

#include <Entity/AssetImporter.h>
#include "CharacterModelAssetEntity.h"

class CharacterModelAssetImporter : public AssetImporter<CharacterModelAssetEntity>
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
  SharedRef<CharacterModelAssetEntity> ImportProcess(AssetMetaData* meta, AssetConverterContext* context) override;

};
