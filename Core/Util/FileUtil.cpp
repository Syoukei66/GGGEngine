#include "FileUtil.h"

#include <fstream>
#include <iostream>

const std::string FileUtil::TextFile_Read(const char* path)
{
  std::ifstream ifs(path);
  if (ifs.fail())
  {
    return nullptr;
  }
  return std::string(
    std::istreambuf_iterator<char>(ifs),
    std::istreambuf_iterator<char>()
  );
}

void FileUtil::TextFile_Write(const char* path, const std::string& str)
{
  std::ofstream ofs(path);
  if (ofs.fail())
  {
    return;
  }
  ofs.write(str.c_str(), str.length());
}
