#include "ModelAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void ModelAssetExporter::ExportProcess(ModelAssetEntity* entity, const AssetConverterContext* context)
{
  CerealIO::Binary::Export(entity->GetAssetInfo()->GetOutputPath().c_str(), entity->GetData());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
