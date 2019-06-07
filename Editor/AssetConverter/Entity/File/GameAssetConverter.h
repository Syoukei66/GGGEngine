#pragma once

#include "FileAssetConverter.h"
#include <Scene/AssetViewer/Material/MaterialViewerBehavior.h>

/*!
 * @brief マテリアルアセットのConverter
 */
template <class Asset_, class AssetData_>
class GameAssetConverter : public FileAssetConverter<Asset_, AssetData_>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameAssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<std::string>& extensions,
    T_UINT32 skip_head, T_UINT32 skip_tail
  )
    : FileAssetConverter<Asset_, AssetData_>(id, class_name, extensions, skip_head, skip_tail)
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual bool CanCreateNewInstance() const override
  {
    return true;
  }

  virtual bool CreateNewInstance(const URI& uri) const
  {
    AssetData_ data = AssetData_();
    std::string output_path = uri.GetFullPath() + "." + this->GetTargetExtensions()[0];
    return CerealIO::Json::SafeExport<AssetData_>(output_path.c_str(), &data);
  }

};
