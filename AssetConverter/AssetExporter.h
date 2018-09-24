#pragma once

#include "Logger.h"

#include <fstream>
#include <unordered_map>

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
  void Export(const std::unordered_map<T_UINT32, Entity_*>& entities, const AssetConverterContext* context);

protected:
  virtual void ExportProcess(Entity_* entity, const AssetConverterContext* context) = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:


  // =================================================================
  // Data Members
  // =================================================================
private:


};

#include "AssetConverterContext.h"

template<class Entity_>
inline void AssetExporter<Entity_>::Export(const std::unordered_map<T_UINT32, Entity_*>& entities, const AssetConverterContext * context)
{
  const Setting* setting = context->GetSetting();

  for (auto& pair : entities)
  {
    AssetInfo* info = pair.second->GetInfo();

    //変換後ファイルが消えているか
    const bool output_file_exists = std::ifstream(setting->output_path + "/" + info->GetLocalFullPath()).is_open();
    const bool asset_changed = info->UpdateTimeStamp();

    //変換対象ファイルのタイムスタンプが一致しているか
    if (output_file_exists && !asset_changed)
    {
      Logger::SkipAssetLog(setting, info);
      continue;
    }
    this->ExportProcess(pair.second, context);
  }
}
