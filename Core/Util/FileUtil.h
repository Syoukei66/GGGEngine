#pragma once

#include <string>

namespace FileUtil
{

const std::string TextFile_Read(const char* path);
void TextFile_Write(const char* path, const std::string& str);
bool IsFileExist(const char* path);

} // namespace FileUtil