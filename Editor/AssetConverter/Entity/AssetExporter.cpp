#include "AssetExporter.h"

#include <fstream>
#include <Converter/AssetConverterContext.h>
#include <Util/FileUtil.h>
#include <Util/Logger.h>
#include "AssetMetaData.h"

// =================================================================
// Methods
// =================================================================
void AssetExporter::Export(AssetMetaData* meta_data, void* mid_data, const AssetConverterContext* context)
{
  //変換後ファイルが消えているか
  const bool output_file_exists = std::ifstream(FileUtil::CreateArchivePath(meta_data)).is_open();
  const bool asset_changed = meta_data->UpdateTimeStamp();

  //変換対象ファイルのタイムスタンプが一致しているか
  if (output_file_exists && !asset_changed)
  {
    Logger::ExportSkipAssetLog(meta_data);
    return;
  }
  this->ExportProcess(meta_data, mid_data, context);
}
