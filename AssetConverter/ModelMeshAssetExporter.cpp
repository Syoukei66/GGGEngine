#include "ModelMeshAssetExporter.h"
#include "Logger.h"

// =================================================================
// Methods
// =================================================================
void ModelMeshAssetExporter::ExportProcess(ModelMeshAssetEntity* entity, const AssetConverterContext* context)
{
  entity->GetData()->Serialize(entity->GetAssetInfo()->GetOutputPath());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
