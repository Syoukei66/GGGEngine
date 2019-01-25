#include <Util/Logger.h>

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <Entity/AssetMetaData.h>
#include <Util/FileUtil.h>

static void FileNameLog(const std::string& path, T_INT32 w)
{
  std::cout << std::left << std::setw(w) << path.substr(std::max(0, (T_INT32)path.length() - w), std::min((size_t)w, path.length()));
}

static void ExportAssetLog(const AssetMetaData* meta, const std::string& action)
{
  std::cout << std::left << std::setw(10) << action + ":";
  FileNameLog(FileUtil::CreateSolutionPath(meta->GetInputPath()), 60);
  std::cout << " => ";                     
  FileNameLog(FileUtil::CreateSolutionPath(meta->GetOutputPath()), 30);
  std::cout << std::endl;
}

void Logger::ImportAssetLog(const URI& uri)
{
  std::cout << "import \"" << uri.GetFullPath() << "\" " << std::endl;
}

void Logger::ImportFromCacheAssetLog(const URI& uri)
{
  std::cout << "import from cache \"" << uri.GetFullPath() << "\" " << std::endl;
}

void Logger::ImportSkipAssetLog(const URI& uri)
{
  std::cout << "skip \"" << uri.GetFullPath() << "\" " << std::endl;
}

void Logger::CommitAssetLog(const AssetMetaData* meta)
{
  std::cout << "commiting \"" << meta->GetURI().GetFullPath() << "\" " << std::endl;
}

void Logger::ConvertAssetLog(const AssetMetaData* meta)
{
  ExportAssetLog(meta, "convert");
}

void Logger::ConvertFaildLog(const AssetMetaData* meta)
{
  ExportAssetLog(meta, "**convert faild**");
}

void Logger::CopyAssetLog(const AssetMetaData* meta)
{
  ExportAssetLog(meta, "copy");
}

void Logger::ExportSkipAssetLog(const AssetMetaData* meta)
{
  ExportAssetLog(meta, "skip");
}
