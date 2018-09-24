#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

static void FileNameLog(const std::string& path, T_INT32 w)
{
  std::cout << std::left << std::setw(w) << path.substr(std::max(0, (T_INT32)path.length() - w), std::min((size_t)w, path.length()));
}

static void ExportAssetLog(const Setting* setting, const AssetInfo* info, const std::string& action)
{
  std::cout << std::left << std::setw(10) << action + ":";
  FileNameLog(info->GetFullPath(), 60);
  std::cout << " => ";
  std::cout << setting->output_path + "/" + info->GetLocalFullPath() << std::endl;
}

void Logger::SkipAssetLog(const Setting* setting, const AssetInfo* info)
{
  ExportAssetLog(setting, info, "skip");
}

void Logger::ConvertAssetLog(const Setting* setting, const AssetInfo* info)
{
  ExportAssetLog(setting, info, "convert");
}

void Logger::CopyAssetLog(const Setting* setting, const AssetInfo* info)
{  
  ExportAssetLog(setting,  info, "copy");
}
