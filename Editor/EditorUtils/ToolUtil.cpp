#include "ToolUtil.h"

#define NOMINMAX
#include <Windows.h>
#include <iostream>

void ToolUtil::Crawl(const std::string& root_path, const std::string& directory_path, std::function<void(const URI& uri)> process)
{
  HANDLE handle;
  WIN32_FIND_DATA data;

  std::string find_file = root_path + directory_path + "*";
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
      Crawl(root_path, directory_path + file_name + "/", process);
      continue;
    }

    process(URI(directory_path.substr(0, directory_path.size() - 1), file_name));
  } while (FindNextFile(handle, &data));

  FindClose(handle);
}