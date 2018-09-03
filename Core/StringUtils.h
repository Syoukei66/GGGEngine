#pragma once

#include <string>
#include "NativeType.h"

namespace StringUtils
{

std::string GetExtension(const std::string& file_path)
{
  return file_path.substr(file_path.length() - file_path.find_last_of("."));
}

}