#pragma once

#include <string>
#include <functional>

class URI;

namespace FileUtil
{

std::string CreateFileName(const std::string& path, const std::string& extension);
std::string CreateProjectFilePath(const std::string& path);
std::string CreateInputPath(const URI& uri);
std::string CreateMidDataPath(const URI& uri);
std::string CreateOutputPath(const URI& uri);

std::string GetTimeStamp(const std::string& path);

void CrawlInputDirectory(std::function<void(const URI& uri)> process);

}