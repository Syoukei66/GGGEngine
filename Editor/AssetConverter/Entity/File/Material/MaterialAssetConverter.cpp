#include "MaterialAssetConverter.h"

// =================================================================
// Methods from AssetConverter
// =================================================================
IAssetDataContainer* MaterialAssetConverter::ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const
{
  std::string output_path = FileUtil::CreateInputPath(entity->GetMetaData()->GetURI());
  MaterialData* data = CerealIO::Json::Import<MaterialData>(output_path.c_str());
  return new AssetDataContainer<MaterialData>(data);
}
