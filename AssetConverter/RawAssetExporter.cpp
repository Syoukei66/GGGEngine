#include "RawAssetExporter.h"

#include "Logger.h"
#include <Windows.h>
#include "AssetConverterContext.h"

// =================================================================
// Methods
// =================================================================
void RawAssetExporter::ExportProcess(RawAssetEntity* entity, const AssetConverterContext* context)
{
  const AssetInfo* info = entity->GetInfo();
  const Setting* setting = context->GetSetting();
  CopyFile(info->GetFullPath().c_str(), (setting->output_path + "/" + info->GetLocalFullPath()).c_str(), false);
  Logger::CopyAssetLog(setting, info);
}
