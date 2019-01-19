#pragma once

#include <Entity/File/FileAssetConverter.h>
#include "TextureAssetConverterSetting.h"

/*!
 * @brief テクスチャアセットのConverter
 */
class TextureAssetConverter : public FileAssetConverter<rcTexture, TextureData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureAssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<std::string>& extensions,
    T_UINT32 skip_head, T_UINT32 skip_tail,
    const SharedRef<AssetViewerBehavior>& viewer
  )
    : FileAssetConverter(id, class_name, extensions, skip_head, skip_tail, viewer)
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual IAssetDataContainer* ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const override;

  virtual std::unique_ptr<ConverterSetting> CreateSetting() const
  {
    return std::unique_ptr<ConverterSetting>(new TextureAssetConverterSetting(this->GetId()));
  }

};
