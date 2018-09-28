#include "ModuleEntity.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

#define NOMINMAX
#include <Windows.h>

static const std::string ENGINE_DIRECTORY_PATH = "Engine";
static const std::string INCLUDE_HEADER = "Include.h";

ModuleEntity::ModuleEntity(const std::string& path)
  : path_(path)
{
  this->AddIgnore(INCLUDE_HEADER);
}

void ModuleEntity::CreateHeaderProgram() const
{
  std::vector<std::string> targets;

  HANDLE handle;
  WIN32_FIND_DATA data;

  std::string find_file = ENGINE_DIRECTORY_PATH + "/" + this->path_ + "/*";
  handle = FindFirstFile(find_file.c_str(), &data);
  if (handle == INVALID_HANDLE_VALUE)
  {
    std::cout << "error Directory not found" << std::endl;
    getchar();
    return;
  }

  //directory_pathで指定されたディレクトリ内のすべてのファイル/ディレクトリに対し処理を行う
  do
  {
    //親ディレクトリを無視
    if (
      (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
      (strcmp(data.cFileName, "..") == 0 || strcmp(data.cFileName, ".") == 0)
      )
    {
      continue;
    }

    std::string file_name = data.cFileName;

    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      continue;
    }

    std::regex re("(.*[^\\.]+)\\.([^\\.]+$)");
    std::smatch result;
    if (!std::regex_match(file_name, result, re))
    {
      continue;
    }

    if (result[2] != "h")
    {
      continue;
    }

    if (this->ignores_.find(file_name) != this->ignores_.end())
    {
      continue;
    }

    targets.push_back(file_name);
  } while (FindNextFile(handle, &data));

  FindClose(handle);

  std::string header;
  header.append("#pragma once\n");
  header.append("\n");
  for (const std::string& path : targets)
  {
    header.append("#include <" + this->path_ + "/" + path + ">\n");
  }
  header.append("\n");
  for (const std::string& path : this->specials_)
  {
    header.append("#include <" + path + ">\n");
  }
  std::ofstream ofs(ENGINE_DIRECTORY_PATH + "/" + this->path_ + "/" + INCLUDE_HEADER);
  ofs << header;
  ofs.close();
}
