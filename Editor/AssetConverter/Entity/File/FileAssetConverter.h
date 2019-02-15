#pragma once

#include <Converter/AssetConverter.h>
#include <Util/Logger.h>

template <class Asset_, class AssetData_>
class FileAssetConverter : public AssetConverter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FileAssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<std::string>& extensions,
    T_UINT32 skip_head, T_UINT32 skip_tail
  )
    : AssetConverter(id, class_name, extensions, skip_head, skip_tail)
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

  virtual void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const
  {
    AssetMetaData* meta_data = entity->GetMetaData();
    CerealIO::Binary::Export<AssetData_>(meta_data->GetOutputPath().c_str(), entity->GetData<AssetData_>());
    Logger::ConvertAssetLog(meta_data);
  }

  virtual bool IsTargetAsset(const std::string& asset_name) const override
  {
    return asset_name == Asset_::ObjectName();
  }

};
