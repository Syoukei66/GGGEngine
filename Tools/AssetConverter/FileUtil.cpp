#include "FileUtil.h"

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <direct.h>

#include <Core/NativeAssert.h>

#include "AssetInfo.h"
#include "Setting.h"
#include "Logger.h"

static const std::string SETTING_PATH = "ConvertSetting.json";
static const std::string UNIQUE_ID_TABLE_PATH = "UniqueIdTable.json";

static const std::string PROJECT_PATH = "./Project";
static const std::string ASSET_PATH = "./Asset";
static const std::string INPUT_PATH = ASSET_PATH + "/Raw";
static const std::string OUTPUT_PATH = ASSET_PATH + "/Archive";
static const std::string MID_DATA_PATH = ASSET_PATH + "/Setting";

void FileUtil::PrepareDirectories()
{
  _mkdir(PROJECT_PATH.c_str());
  _mkdir(ASSET_PATH.c_str());
  _mkdir(INPUT_PATH.c_str());
  _mkdir(OUTPUT_PATH.c_str());
  _mkdir(MID_DATA_PATH.c_str());
}

std::string FileUtil::GetSettingPath()
{
  return CreateMidDataPath(SETTING_PATH);
}

std::string FileUtil::GetUniqueIdTablePath()
{
  return CreateMidDataPath(UNIQUE_ID_TABLE_PATH);
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

std::string FileUtil::CreateOutputPath(const URI& uri)
{
  return OUTPUT_PATH + "/" + uri.GetFullPath();
}

void FileUtil::CopyRawAsset(const AssetInfo* info)
{
  HRESULT hr = CopyFile(
    info->GetInputPath().c_str(),
    info->GetOutputPath().c_str(),
    false
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "コピーに失敗しました");
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

void Crawl(const std::string& root_path, const std::string& directory_path, std::function<void(const URI& uri)> process)
{
  HANDLE handle;
  WIN32_FIND_DATA data;

  std::string find_file = root_path + directory_path + "*";
  handle = FindFirstFile(find_file.c_str(), &data);
  if (handle == INVALID_HANDLE_VALUE)
  {
    std::cout << "error Asset File not found" << std::endl;
    getchar();
    return;
  }

  //directory_pathで指定されたディレクトリ内のすべてのファイル/ディレクトリに対し処理を行う
  do
  {
    //親ディレクトリを無視
    if (
      (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
      (strcmp(data.cFileName, "..") == 0 || strcmp(data.cFileName, ".") == 0)
      )
    {
      continue;
    }

    std::string file_name = data.cFileName;

    //ディレクトリだった場合はそのディレクトリに対しても処理を行う
    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      Crawl(root_path, directory_path + file_name + "/", process);
      continue;
    }

    process(URI(directory_path.substr(0, directory_path.size() - 1), file_name));
  } while (FindNextFile(handle, &data));

  FindClose(handle);
}

void FileUtil::CrawlInputDirectory(std::function<void(const URI& uri)> process)
{
  Crawl(INPUT_PATH + "/", "", process);
}
