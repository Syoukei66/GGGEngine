#pragma once

#include <string>
#include <functional>

namespace Util
{

namespace File
{

std::string GetTimeStamp(const std::string& path);
void Crawl(const std::string& directory_path, std::function<void(const std::string& directory_path, const std::string& file_name)> process);

}

}