#include "ProjectEntity.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

#define NOMINMAX
#include <Windows.h>

static const std::string ENGINE_DIRECTORY_PATH = "Engine";
static const std::string SERIALIZER_FILENAME = "Include.h";
static const std::string SERIALIZER_HEADER = SERIALIZER_FILENAME + ".h";
static const std::string SERIALIZER_CPP = SERIALIZER_FILENAME + ".cpp";

static std::vector<std::string> TARGET_EXTENSION = { "h", "cpp", "hpp", "inl"};

ProjectEntity::ProjectEntity(const std::string& path)
  : path_(path)
{

}

ProjectEntity::~ProjectEntity()
{

}

void ProjectEntity::CreateProgram(std::string* header, std::string* cpp) const
{
  std::vector<std::string> targets;

  this->Crawl("", &targets);

}

void ProjectEntity::Crawl(const std::string& path, std::vector<std::string>* dest) const
{
  HANDLE handle;
  WIN32_FIND_DATA data;

  std::string find_file = ENGINE_DIRECTORY_PATH + "/" + this->path_ + path + "/*";
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
      Crawl(path + "/" + data.cFileName, dest);
      continue;
    }

    std::regex re("(.*[^\\.]+)\\.([^\\.]+$)");
    std::smatch result;
    if (!std::regex_match(file_name, result, re))
    {
      continue;
    }

    if (std::find(TARGET_EXTENSION.begin(), TARGET_EXTENSION.end(), result[2]) == TARGET_EXTENSION.end())
    {
      continue;
    }

    (*dest).push_back(path + "/" + file_name);
  } while (FindNextFile(handle, &data));

  FindClose(handle);

}
