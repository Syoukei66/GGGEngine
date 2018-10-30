#pragma once

namespace StringUtils
{

static std::string GetExtension(const std::string& file_path)
{
  return file_path.substr(file_path.length() - file_path.find_last_of("."));
}

}