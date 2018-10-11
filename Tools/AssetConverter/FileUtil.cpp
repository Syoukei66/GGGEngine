#include "FileUtil.h"

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <direct.h>

#include <Core/NativeAssert.h>
#include <ToolUtil.h>

#include <Core/Directory.h>

#include "AssetInfo.h"
#include "Setting.h"
#include "Logger.h"

static const std::string SETTING_PATH = "ConvertSetting.json";

static const std::string PROJECT_PATH = "Project";
static const std::string ASSET_PATH = "AssetConverter";
static const std::string RUNTIME_ASSET_PATH = "Asset";

static const std::string INPUT_PATH = ASSET_PATH + "/Raw";
static const std::string ARCHIVE_PATH = ASSET_PATH + "/Archive";
static const std::string MID_DATA_PATH = ASSET_PATH + "/Setting";

void FileUtil::PrepareDirectories()
{
  _mkdir(PROJECT_PATH.c_str());
  _mkdir(ASSET_PATH.c_str());
  _mkdir(INPUT_PATH.c_str());
  _mkdir(ARCHIVE_PATH.c_str());
  _mkdir(MID_DATA_PATH.c_str());
  _mkdir(MID_DATA_PATH.c_str());
  _mkdir(RUNTIME_ASSET_PATH.c_str());
}

std::string FileUtil::GetSettingPath()
{
  return CreateMidDataPath(SETTING_PATH);
}

std::string FileUtil::GetMidDataUniqueIdTablePath()
{
  return CreateMidDataPath(Directory::GetUniqueIdTableFileName("json"));
}

std::string FileUtil::GetArchiveUniqueIdTablePath()
{
  return Directory::GetArchiveUniqueIdTablePath();
}

std::string FileUtil::CreateFileName(const std::string& path, const std::string& extension)
{
  return path + "." + extension;
}

std::string FileUtil::CreateProjectFilePath(const std::string& path)
{
  return PROJECT_PATH + "/" + path;
}

std::string FileUtil::CreateInputPath(const URI& uri)
{
  return INPUT_PATH + "/" + uri.GetFullPath();
}

std::string FileUtil::CreateMidDataPath(const URI& uri)
{
  return MID_DATA_PATH + "/" + uri.GetFullPath();
}

std::string FileUtil::CreateOutputPath(const AssetInfo* info)
{
  //return ARCHIVE_PATH + "/" + std::to_string(info->GetUniqueID()) + "." + info->GetURI().GetExtension();
  return RUNTIME_ASSET_PATH + "/" + std::to_string(info->GetUniqueID()) + "." + info->GetURI().GetExtension();
}

std::string FileUtil::CreateRuntimeAssetPath(const URI& uri)
{
  return RUNTIME_ASSET_PATH + "/" + uri.GetFullPath();
}

void FileUtil::CopyRawAsset(const AssetInfo* info)
{
  HRESULT hr = CopyFile(
    info->GetInputPath().c_str(),
    info->GetOutputPath().c_str(),
    false
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "ÉRÉsÅ[Ç…é∏îsÇµÇ‹ÇµÇΩ");
  Logger::CopyAssetLog(info);
}

std::string FileUtil::GetTimeStamp(const std::string& path)
{
  HANDLE source_file = CreateFile(path.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  FILETIME ft;
  SYSTEMTIME st;
  GetFileTime(source_file, NULL, NULL, &ft);
  CloseHandle(source_file);
  FileTimeToSystemTime(&ft, &st);

  std::string ret = std::string();
  ret.append(std::to_string(st.wYear));
  ret.append("/");
  ret.append(std::to_string(st.wMonth));
  ret.append("/");
  ret.append(std::to_string(st.wDay));
  ret.append(" ");
  ret.append(std::to_string(st.wHour));
  ret.append(":");
  ret.append(std::to_string(st.wMinute));
  return ret;
}

void FileUtil::CrawlInputDirectory(std::function<void(const URI& uri)> process)
{
  ToolUtil::Crawl(INPUT_PATH + "/", "", process);
}
