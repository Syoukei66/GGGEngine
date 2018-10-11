#include "DefaultMeshAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void DefaultMeshAssetExporter::ExportProcess(DefaultMeshAssetEntity* entity, const AssetConverterContext* context)
{
  entity->GetData()->Serialize(entity->GetAssetInfo()->GetOutputPath());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
