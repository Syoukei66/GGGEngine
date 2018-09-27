#pragma once

#include <string>
#include <functional>

class URI;
class AssetInfo;

namespace FileUtil
{

void PrepareDirectories();

std::string GetSettingPath();
std::string GetUniqueIdTablePath();

std::string CreateFileName(const std::string& path, const std::string& extension);
std::string CreateProjectFilePath(const std::string& path);
std::string CreateInputPath(const URI& uri);
std::string CreateMidDataPath(const URI& uri);
std::string CreateOutputPath(const URI& uri);

void CopyRawAsset(const AssetInfo* info);

std::string GetTimeStamp(const std::string& path);

void CrawlInputDirectory(std::function<void(const URI& uri)> process);

}