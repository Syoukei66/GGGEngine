#include "ModelAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void ModelAssetExporter::ExportProcess(ModelAssetEntity* entity, const AssetConverterContext* context)
{
  entity->GetData()->Serialize(entity->GetAssetInfo()->GetOutputPath());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
