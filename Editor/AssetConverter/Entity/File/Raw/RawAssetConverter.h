#pragma once

#include <Converter/AssetConverter.h>
#include "RawAssetImporter.h"
#include "RawAssetExporter.h"

template <class Asset_>
class RawAssetConverter : public AssetConverter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RawAssetConverter(
    const std::string& id,
    const std::string& class_name,
    std::initializer_list<std::string> extensions
  )
    : AssetConverter(
      id,
      new RawAssetImporter(extensions),
      new RawAssetExporter(),
      new AssetProgramGenerator(id, class_name, 1, 0)
    )
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual void RegisterAssetManager(const SharedRef<AssetEntity>& entity) override
  {
    AssetMetaData* meta_data = entity->GetMetaData();
    AssetManager::AddAsset<Asset_>(
      meta_data->GetUniqueID(),
      meta_data->GetURI().GetExtension(),
      Asset_::CreateFromFile(meta_data->GetInputPath().c_str())
      );
  }

};
