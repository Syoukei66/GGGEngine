#pragma once

class AssetConverterContext;

template <class Entity_>
class AssetExporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetExporter()
  {
  }

  virtual ~AssetExporter()
  {
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  void Export(const std::unordered_map<T_UINT32, SharedRef<Entity_>>& entities, const AssetConverterContext* context);

protected:
  virtual void ExportProcess(const SharedRef<Entity_>& entity, const AssetConverterContext* context) = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:


  // =================================================================
  // Data Members
  // =================================================================
private:


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
    AssetInfo* info = pair.second->GetAssetInfo();

    //変換後ファイルが消えているか
    const bool output_file_exists = std::ifstream(FileUtil::CreateArchivePath(info)).is_open();
    const bool asset_changed = info->UpdateTimeStamp();

    //変換対象ファイルのタイムスタンプが一致しているか
    if (output_file_exists && !asset_changed)
    {
      Logger::ExportSkipAssetLog(info);
      continue;
    }
    this->ExportProcess(pair.second, context);
  }
}
