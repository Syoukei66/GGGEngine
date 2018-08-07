#include "FileUtil.h"

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <fstream>

std::string Util::File::GetTimeStamp(const std::string & path)
{
  HANDLE source_file = CreateFile(path.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  FILETIME ft;
  SYSTEMTIME st;
  GetFileTime(source_file, NULL, NULL, &ft);
  CloseHandle(source_file);
  FileTimeToSystemTime(&ft, &st);

  std::string ret = std::string();
  ret.append(std::to_string(st.wYear));
  ret.append("/");
  ret.append(std::to_string(st.wMonth));
  ret.append("/");
  ret.append(std::to_string(st.wDay));
  ret.append(" ");
  ret.append(std::to_string(st.wHour));
  ret.append(":");
  ret.append(std::to_string(st.wMinute));
  return ret;
}
