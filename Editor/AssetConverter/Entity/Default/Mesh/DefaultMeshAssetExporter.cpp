#include "DefaultMeshAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void DefaultMeshAssetExporter::ExportProcess(const SharedRef<DefaultMeshAssetEntity>& entity, const AssetConverterContext* context)
{
  CerealIO::Binary::Export(entity->GetMetaData()->GetOutputPath().c_str(), entity->GetData());
  Logger::ConvertAssetLog(entity->GetMetaData());
}
