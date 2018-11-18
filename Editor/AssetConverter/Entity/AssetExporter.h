#pragma once

class AssetConverterContext;

template <class Entity_>
class AssetExporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetExporter() = default;
  virtual ~AssetExporter() = default;
 
  // =================================================================
  // Methods
  // =================================================================
public:
  void Export(const std::unordered_map<T_UINT32, SharedRef<Entity_>>& entities, const AssetConverterContext* context);

protected:
  virtual void ExportProcess(const SharedRef<Entity_>& entity, const AssetConverterContext* context) = 0;

};

#include <fstream>
#include <Converter/AssetConverterContext.h>
#include <Util/FileUtil.h>
#include <Util/Logger.h>

// =================================================================
// Methods
// =================================================================
template<class Entity_>
inline void AssetExporter<Entity_>::Export(const std::unordered_map<T_UINT32, SharedRef<Entity_>>& entities, const AssetConverterContext* context)
{
  for (auto& pair : entities)
  {
    AssetMetaData* meta = pair.second->GetMetaData();

    //変換後ファイルが消えているか
    const bool output_file_exists = std::ifstream(FileUtil::CreateArchivePath(meta)).is_open();
    const bool asset_changed = meta->UpdateTimeStamp();

    //変換対象ファイルのタイムスタンプが一致しているか
    if (output_file_exists && !asset_changed)
    {
      Logger::ExportSkipAssetLog(meta);
      continue;
    }
    this->ExportProcess(pair.second, context);
  }
}
