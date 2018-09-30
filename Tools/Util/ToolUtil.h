#pragma once

#include <string>
#include <functional>

#include "URI.h"

namespace ToolUtil
{

void Crawl(const std::string& root_path, const std::string& directory_path, std::function<void(const URI& uri)> process);

}