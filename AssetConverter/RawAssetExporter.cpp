#include "RawAssetExporter.h"

#include "Logger.h"
#include <Windows.h>
#include "AssetConverterContext.h"

// =================================================================
// Methods
// =================================================================
void RawAssetExporter::ExportProcess(RawAssetEntity* entity, const AssetConverterContext* context)
{
  const AssetInfo* info = entity->GetAssetInfo();
  CopyFile(
    FileUtil::CreateInputPath(info->GetURI().GetFullPath()).c_str(),
    FileUtil::CreateOutputPath(info->GetURI().GetFullPath()).c_str(),
    false
  );
  Logger::CopyAssetLog(info);
}
