#pragma once

#include <string>

#include "AssetMetaData.h"

struct AssetInfo
{
  AssetMetaData* meta_data;
  std::string full_path;
  std::string directory_path;
  std::string file_name;
  std::string extension;
  std::string output_path;
  std::string program_id;
};