#include "DefaultMaterialAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void DefaultMaterialAssetExporter::ExportProcess(DefaultMaterialAssetEntity* entity, const AssetConverterContext* context)
{
  entity->GetData()->Serialize(entity->GetAssetInfo()->GetOutputPath());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
