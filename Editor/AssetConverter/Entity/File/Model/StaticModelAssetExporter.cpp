#include "StaticModelAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void StaticModelAssetExporter::ExportProcess(const SharedRef<StaticModelAssetEntity>& entity, const AssetConverterContext* context)
{
  CerealIO::Binary::Export(entity->GetMetaData()->GetOutputPath().c_str(), entity->GetData());
  Logger::ConvertAssetLog(entity->GetMetaData());
}
