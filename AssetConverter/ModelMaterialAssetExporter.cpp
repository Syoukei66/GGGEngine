#include "ModelMaterialAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void ModelMaterialAssetExporter::ExportProcess(ModelMaterialAssetEntity* entity, const AssetConverterContext* context)
{
  entity->GetData()->Serialize(entity->GetAssetInfo()->GetOutputPath());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
