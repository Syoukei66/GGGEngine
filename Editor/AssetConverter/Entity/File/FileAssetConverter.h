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
    const std::string& class_name, T_UINT32 skip_head, T_UINT32 skip_tail
  )
    : AssetConverter(
      id,
      importer, 
      new FileAssetExporter<AssetData_>(), 
      new AssetProgramGenerator(id, class_name, skip_head, skip_tail)
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
      Asset_::Create(*(AssetData_*)entity->GetData())
      );
  }

};
