#pragma once

#include <Converter/AssetConverter.h>

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
      class_name,
      extensions,
      1, 0
    )
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual void RegisterAssetManager(const SharedRef<AssetEntity>& entity) const override
  {
    AssetMetaData* meta_data = entity->GetMetaData();
    AssetManager::AddAsset<Asset_>(
      meta_data->GetUniqueID(),
      meta_data->GetURI().GetExtension(),
      Asset_::CreateFromFile(meta_data->GetInputPath().c_str())
      );
  }

  virtual IAssetDataContainer* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const override
  {
    return new AssetDataContainer<Asset_>(nullptr, this);
  }

  virtual void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const
  {
    FileUtil::CopyRawAsset(entity->GetMetaData());
  }

};
