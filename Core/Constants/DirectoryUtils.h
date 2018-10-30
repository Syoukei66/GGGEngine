#pragma once

namespace Directory
{

static std::string GetUniqueIdTableFileName(const std::string& extension)
{
  return "UniqueIdTable." + extension;
}

static std::string GetAssetDirectory()
{
  return "./Asset";
}

static std::string GetArchiveUniqueIdTablePath()
{
  return GetAssetDirectory() + "/" + GetUniqueIdTableFileName("bin");
}

}