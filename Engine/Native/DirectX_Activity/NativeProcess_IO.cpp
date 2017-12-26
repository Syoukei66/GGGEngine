#include "NativeProcess_IO.h"
#include <fstream>

const std::string NativeProcess_IO::TextFile_Read(const char* path)
{
  std::ifstream ifs(path);
  if (ifs.fail())
  {
    return nullptr;
  }
  return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}
