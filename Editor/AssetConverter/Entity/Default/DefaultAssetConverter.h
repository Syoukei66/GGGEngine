#pragma once

#include <Converter/AssetConverter.h>
#include <Util/Logger.h>

#include "DefaultAssetConverterSetting.h"

template <class Asset_, class AssetData_, class ViewerBehavior_>
class DefaultAssetConverter : public AssetConverter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefaultAssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<T_UINT32>& default_sub_assets
  )
    : AssetConverter(id, class_name, {}, 2, 0)
    , default_sub_assets_(default_sub_assets)
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual IAssetDataContainer* ImportFromCache(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const override
  {
    AssetMetaData* meta_data = entity->GetMetaData();
    const std::string& path = FileUtil::CreateCachePath(entity->GetMetaData()->GetURI());
    AssetData_* data = CerealIO::Binary::SafeImport<AssetData_>(path.c_str());
    if (!data)
    {
      return nullptr;
    }
    return new AssetDataContainer<AssetData_>(data);
  }

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
    DefaultAssetConverterSetting* ret = new DefaultAssetConverterSetting(this->GetId());
    for (T_UINT32 uid : this->default_sub_assets_)
    {
      ret->AddSubAsset(uid);
    }
    return std::unique_ptr<ConverterSetting>(ret);
  }

  virtual SharedRef<AssetViewerBehavior> CreateViewerBehavior() const override
  {
    return ViewerBehavior_::Create();
  }

  virtual bool IsTargetAsset(const std::string& asset_name) const override
  {
    return asset_name == Asset_::ObjectName();
  }

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
private:
  std::vector<T_UINT32> default_sub_assets_;

};