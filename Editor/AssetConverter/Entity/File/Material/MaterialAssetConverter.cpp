#include "MaterialAssetConverter.h"
#include <Constants/Extensions.h>

// =================================================================
// Methods from AssetConverter
// =================================================================
IAssetDataContainer* MaterialAssetConverter::ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const
{
  ConverterSetting* setting = entity->GetMetaData()->GetConverterSetting().get();
  setting->ClearSubAssets();
  std::string output_path = FileUtil::CreateInputPath(entity->GetMetaData()->GetURI());
  MaterialData* data = CerealIO::Json::Import<MaterialData>(output_path.c_str());
  setting->AddSubAsset(data->shader_unique_id_);
  for (T_FIXED_UINT32 uid : data->textures_)
  {
    setting->AddSubAsset(uid);
  }
  return new AssetDataContainer<MaterialData>(data);
}

bool MaterialAssetConverter::CreateNewInstance(const URI& uri) const
{
  MaterialData data = MaterialData();
  std::string output_path = uri.GetFullPath() + "." + Extensions::MATERIAL;
  return CerealIO::Json::SafeExport<MaterialData>(output_path.c_str(), &data);
}
