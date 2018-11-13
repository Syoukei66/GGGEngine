#include <Util/Logger.h>

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <Entity/AssetInfo.h>
#include <Util/FileUtil.h>

static void FileNameLog(const std::string& path, T_INT32 w)
{
  std::cout << std::left << std::setw(w) << path.substr(std::max(0, (T_INT32)path.length() - w), std::min((size_t)w, path.length()));
}

static void ExportAssetLog(const AssetInfo* info, const std::string& action)
{
  std::cout << std::left << std::setw(10) << action + ":";
  FileNameLog(FileUtil::CreateSolutionPath(info->GetInputPath()), 60);
  std::cout << " => ";
  FileNameLog(FileUtil::CreateSolutionPath(info->GetOutputPath()), 30);
  std::cout << std::endl;
}

void Logger::ImportAssetLog(const URI& uri)
{
  std::cout << "importing \"" << uri.GetFullPath() << "\" " << std::endl;
}

void Logger::ImportSkipAssetLog(const URI& uri)
{
  std::cout << "skip \"" << uri.GetFullPath() << "\" " << std::endl;
}

void Logger::CommitAssetLog(const AssetInfo* info)
{
  std::cout << "commiting \"" << info->GetURI().GetFullPath() << "\" " << std::endl;
}

void Logger::ConvertAssetLog(const AssetInfo* info)
{
  ExportAssetLog(info, "convert");
}

void Logger::CopyAssetLog(const AssetInfo* info)
{
  ExportAssetLog(info, "copy");
}

void Logger::ExportSkipAssetLog(const AssetInfo* info)
{
  ExportAssetLog(info, "skip");
}
