#pragma once

#include "AssetImporter.h"
#include "RawAssetEntity.h"

//生データから特に変換などが行われないアセットのインポータ―
class RawAssetImporter : public AssetImporter<RawAssetEntity>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RawAssetImporter(const std::vector<std::string>& extensions);

  // =================================================================
  // Methods
  // =================================================================
protected:
  RawAssetEntity* ImportProcess(AssetInfo* info, AssetConverterContext* context) override;

};
