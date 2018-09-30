#pragma once

#include <string>
#include <vector>
#include "ProgramEntity.h"

class ProjectEntity
{
public:
  ProjectEntity(const std::string& path);
  ~ProjectEntity();

public:
  void Crawl();
  void CreateProgram(std::string* header, std::string* cpp);

private:
  std::string path_;
  std::vector<TypeEntity*> type_entities_;

};
