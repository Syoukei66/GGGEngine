#pragma once

#include <Entity/File/FileAssetConverter.h>
#include <Scene/AssetViewer/CharacterModel/CharacterModelViewerBehavior.h>
#include "CharacterModelConverterSetting.h"

class CharacterModelAssetConverter : public FileAssetConverter<rcCharacterModel, CharacterModelData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CharacterModelAssetConverter(
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
  virtual IAssetDataContainer* ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const override;

  virtual std::unique_ptr<ConverterSetting> CreateSetting() const
  {
    return std::unique_ptr<ConverterSetting>(new CharacterModelAssetConverterSetting(this->GetId()));
  }

  virtual SharedRef<AssetViewerBehavior> CreateViewerBehavior() const override
  {
    return CharacterModelViewerBehavior::Create();
  }
};
