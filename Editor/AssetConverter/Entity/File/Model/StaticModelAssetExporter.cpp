#include "StaticModelAssetExporter.h"

// =================================================================
// Methods
// =================================================================
void StaticModelAssetExporter::ExportProcess(const SharedRef<StaticModelAssetEntity>& entity, const AssetConverterContext* context)
{
  CerealIO::Binary::Export(entity->GetAssetInfo()->GetOutputPath().c_str(), entity->GetData());
  Logger::ConvertAssetLog(entity->GetAssetInfo());
}
