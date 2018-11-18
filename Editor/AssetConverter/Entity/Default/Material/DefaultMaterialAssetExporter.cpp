#include "DefaultMaterialAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void DefaultMaterialAssetExporter::ExportProcess(const SharedRef<DefaultMaterialAssetEntity>& entity, const AssetConverterContext* context)
{
  CerealIO::Binary::Export(entity->GetMetaData()->GetOutputPath().c_str(), entity->GetData());
  Logger::ConvertAssetLog(entity->GetMetaData());
}
