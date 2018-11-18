#include "ModelMeshAssetExporter.h"
#include <Util/Logger.h>

// =================================================================
// Methods
// =================================================================
void ModelMeshAssetExporter::ExportProcess(const SharedRef<ModelMeshAssetEntity>& entity, const AssetConverterContext* context)
{
  CerealIO::Binary::Export(entity->GetMetaData()->GetOutputPath().c_str(), entity->GetData());
  Logger::ConvertAssetLog(entity->GetMetaData());
}
