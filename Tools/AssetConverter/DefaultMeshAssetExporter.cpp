#include "DefaultMeshAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void DefaultMeshAssetExporter::ExportProcess(DefaultMeshAssetEntity* entity, const AssetConverterContext* context)
{
  CerealIO::Binary::Export(entity->GetAssetInfo()->GetOutputPath().c_str(), entity->GetData());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
