#include "ModelMeshAssetExporter.h"
#include <Util/Logger.h>

// =================================================================
// Methods
// =================================================================
void ModelMeshAssetExporter::ExportProcess(ModelMeshAssetEntity* entity, const AssetConverterContext* context)
{
  CerealIO::Binary::Export(entity->GetAssetInfo()->GetOutputPath().c_str(), entity->GetData());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
