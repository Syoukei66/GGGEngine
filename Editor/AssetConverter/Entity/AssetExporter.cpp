#include "AssetExporter.h"

#include <fstream>
#include <Converter/AssetConverterContext.h>
#include <Util/FileUtil.h>
#include <Util/Logger.h>

// =================================================================
// Methods
// =================================================================
void AssetExporter::Export(const std::unordered_map<T_UINT32, SharedRef<AssetEntity>>& entities, const AssetConverterContext* context)
{
  for (auto& pair : entities)
  {
    AssetMetaData* meta = pair.second->GetMetaData();

    //�ϊ���t�@�C���������Ă��邩
    const bool output_file_exists = std::ifstream(FileUtil::CreateArchivePath(meta)).is_open();
    const bool asset_changed = meta->UpdateTimeStamp();

    //�ϊ��Ώۃt�@�C���̃^�C���X�^���v����v���Ă��邩
    if (output_file_exists && !asset_changed)
    {
      Logger::ExportSkipAssetLog(meta);
      continue;
    }
    this->ExportProcess(pair.second, context);
  }
}
