#include "NotConverter.h"

#include "Logger.h"
#include <Windows.h>
#include <algorithm>

NotConverter::NotConverter(const std::initializer_list<std::string>& extensions, const std::string& asset_name, const std::string& class_name)
  : extensions_(extensions)
  , asset_name_(asset_name)
  , class_name_(class_name)
{
  this->GetNamespaceGenerator().AddAsset(asset_name, class_name);
}

void NotConverter::GetIncludePaths(std::set<std::string>* dest) const
{
}

bool NotConverter::IsTarget(const std::string& extension) const
{
  return std::find(this->extensions_.begin(), this->extensions_.end(), extension) != this->extensions_.end();
}

void NotConverter::ConvertProcess(AssetInfo* info) const
{
  CopyFile(info->full_path.c_str(), info->output_path.c_str(), false);
  Logger::CopyAssetLog(info);
}
