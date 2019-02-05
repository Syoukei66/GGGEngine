#pragma once

#include <Entity/File/FileAssetConverter.h>
#include <Scene/AssetViewer/StaticMesh/StaticMeshViewerBehavior.h>
#include "MeshAssetConverterSetting.h"

/*!
 * @brief マテリアルアセットのConverter
 */
class MeshAssetConverter : public FileAssetConverter<rcMesh, StaticMeshData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshAssetConverter(
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
    return std::unique_ptr<ConverterSetting>(new MeshAssetConverterSetting(this->GetId()));
  }

  virtual SharedRef<AssetViewerBehavior> CreateViewerBehavior() const override
  {
    return StaticMeshViewerBehavior::Create();
  }
};
