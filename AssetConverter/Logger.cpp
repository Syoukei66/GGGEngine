#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

static void FileNameLog(const std::string& path, T_INT32 w)
{
  std::cout << std::left << std::setw(w) << path.substr(std::max(0, (T_INT32)path.length() - w), std::min((size_t)w, path.length()));
}

static void AssetLog(const AssetInfo* info, const std::string& action)
{
  std::cout << std::left << std::setw(10) << action + ":";
  FileNameLog(info->full_path, 60);
  std::cout << " => ";
  std::cout << info->output_path << std::endl;
}

void Logger::SkipAssetLog(const AssetInfo* info)
{
  AssetLog(info, "skip");
}

void Logger::ConvertAssetLog(const AssetInfo* info)
{
  AssetLog(info, "convert");
}

void Logger::CopyAssetLog(const AssetInfo* info)
{  
  AssetLog(info, "copy");
}
