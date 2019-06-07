#pragma once

#include <Entity/File/GameAssetConverter.h>
#include <Scene/AssetViewer/Material/MaterialViewerBehavior.h>
#include "MaterialAssetConverterSetting.h"

/*!
 * @brief マテリアルアセットのConverter
 */
class MaterialAssetConverter : public GameAssetConverter<rcMaterial, MaterialData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MaterialAssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<std::string>& extensions,
    T_UINT32 skip_head, T_UINT32 skip_tail
  )
    : GameAssetConverter(id, class_name, extensions, skip_head, skip_tail)
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual IAssetDataContainer* ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const override;

  virtual std::unique_ptr<ConverterSetting> CreateSetting() const
  {
    return std::unique_ptr<ConverterSetting>(new MaterialAssetConverterSetting(this->GetId()));
  }

  virtual SharedRef<AssetViewerBehavior> CreateViewerBehavior() const override
  {
    return MaterialViewerBehavior::Create();
  }
};
