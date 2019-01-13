#pragma once

#include <Converter/AssetConverter.h>
#include "FileAssetExporter.h"

template <class Asset_, class AssetData_>
class FileAssetConverter : public AssetConverter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FileAssetConverter(
    const std::string& id,
    AssetImporter* importer,
    const std::string& asset_name, const std::string& class_name, T_UINT32 skip_head, T_UINT32 skip_tail
  )
    : AssetConverter(
      id,
      importer, 
      new FileAssetExporter<AssetData_>(), 
      new AssetProgramGenerator(asset_name, class_name, skip_head, skip_tail)
    )
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension, void* mid_data) override
  {
    AssetManager::AddAsset(uid, extension, Asset_::Create((AssetData_*)mid_data));
  }

};
