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

void Util::File::Crawl(const std::string& directory_path, std::function<void(const std::string&directory_path, const std::string&file_name)> process)
{
  HANDLE handle;
  WIN32_FIND_DATA data;

  std::string find_file = directory_path + "*";
  handle = FindFirstFile(find_file.c_str(), &data);
  if (handle == INVALID_HANDLE_VALUE)
  {
    std::cout << "error Asset File not found" << std::endl;
    getchar();
    return;
  }

  //directory_path�Ŏw�肳�ꂽ�f�B���N�g�����̂��ׂẴt�@�C��/�f�B���N�g���ɑ΂��������s��
  do
  {
    //�e�f�B���N�g���𖳎�
    if (
      (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
      (strcmp(data.cFileName, "..") == 0 || strcmp(data.cFileName, ".") == 0)
      )
    {
      continue;
    }

    std::string file_name = data.cFileName;

    //�f�B���N�g���������ꍇ�͂��̃f�B���N�g���ɑ΂��Ă��������s��
    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      Crawl(directory_path + file_name + "/", process);
      continue;
    }

    process(directory_path, file_name);
  } while (FindNextFile(handle, &data));

  FindClose(handle);
}
