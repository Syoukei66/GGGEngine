#pragma once

#include <Converter/AssetConverter.h>
#include <Util/Logger.h>

#include "DefaultAssetConverterSetting.h"

template <class Asset_, class AssetData_>
class DefaultAssetConverter : public AssetConverter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefaultAssetConverter(
    const std::string& id,
    const std::string& class_name
  )
    : AssetConverter(id, class_name, {}, 2, 0)
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
      Asset_::Create(*entity->GetData<AssetData_>())
      );
  }

  virtual IAssetDataContainer* ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const override
  {
    return entity->GetDataContainer();
  }

  virtual void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const
  {
    AssetMetaData* meta_data = entity->GetMetaData();
    CerealIO::Binary::Export<AssetData_>(meta_data->GetOutputPath().c_str(), entity->GetData<AssetData_>());
    Logger::ConvertAssetLog(meta_data);
  }
  
  virtual std::unique_ptr<ConverterSetting> CreateSetting() const
  {
    return std::unique_ptr<ConverterSetting>(new DefaultAssetConverterSetting(this->GetId()));
  }

};