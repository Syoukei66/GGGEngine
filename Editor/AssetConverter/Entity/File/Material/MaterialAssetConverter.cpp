#include "MaterialAssetConverter.h"

// =================================================================
// Methods from AssetConverter
// =================================================================
IAssetDataContainer* MaterialAssetConverter::ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const
{
  MaterialAssetConverterSetting* setting = static_cast<MaterialAssetConverterSetting*>(entity->GetMetaData()->GetConverterSetting().get());
  MaterialData* data = nullptr;
  if (setting->is_master_)
  {
    data = new MaterialData(setting->edit_data_);
  }
  else
  {
    std::string output_path = FileUtil::CreateInputPath(entity->GetMetaData()->GetURI());
    data = CerealIO::Json::Import<MaterialData>(output_path.c_str());
  }
  return new AssetDataContainer<MaterialData>(data);
}
