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
  //�ϊ���t�@�C���������Ă��邩
  const bool output_file_exists = std::ifstream(FileUtil::CreateArchivePath(meta_data)).is_open();
  const bool asset_changed = meta_data->UpdateTimeStamp();

  //�ϊ��Ώۃt�@�C���̃^�C���X�^���v����v���Ă��邩
  if (output_file_exists && !asset_changed)
  {
    Logger::ExportSkipAssetLog(meta_data);
    return;
  }
  this->ExportProcess(meta_data, mid_data, context);
}
