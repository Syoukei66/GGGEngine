#pragma once

#include <Entity/File/FileAssetConverter.h>
#include <Scene/AssetViewer/StaticModel/StaticModelViewerBehavior.h>
#include "StaticModelConverterSetting.h"

class StaticModelAssetConverter : public FileAssetConverter<rcStaticModel, StaticModelData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  StaticModelAssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<std::string>& extensions,
    T_UINT32 skip_head, T_UINT32 skip_tail
  )
    : FileAssetConverter(id, class_name, extensions, skip_head, skip_tail)
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual bool CanCreateNewInstance() const override
  {
    return false;
  }

  virtual bool CreateNewInstance(const URI& uri) const
  {
    return false;
  }

  virtual IAssetDataContainer* ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const override;

  virtual std::unique_ptr<ConverterSetting> CreateSetting() const
  {
    return std::unique_ptr<ConverterSetting>(new StaticModelAssetConverterSetting(this->GetId()));
  }

  virtual SharedRef<AssetViewerBehavior> CreateViewerBehavior() const override
  {
    return StaticModelViewerBehavior::Create();
  }
};
