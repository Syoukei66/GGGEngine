#include "MaterialAssetConverter.h"

// =================================================================
// Methods from AssetConverter
// =================================================================
IAssetDataContainer* MaterialAssetConverter::ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const
{
  MaterialAssetConverterSetting* setting = static_cast<MaterialAssetConverterSetting*>(entity->GetMetaData()->GetConverterSetting().get());
  MaterialData* data = nullptr;
  if (setting->editor.IsMaster())
  {
    data = new MaterialData(setting->editor.GetEditData());
  }
  else
  {
    setting->ClearSubAssets();
    std::string output_path = FileUtil::CreateInputPath(entity->GetMetaData()->GetURI());
    data = CerealIO::Json::Import<MaterialData>(output_path.c_str());
    for (T_FIXED_UINT32 uid : data->textures_)
    {
      setting->AddSubAsset(uid);
    }
  }
  return new AssetDataContainer<MaterialData>(data);
}
