#pragma once

#include <string>
#include <vector>
#include "ClassEntity.h"

class ProjectEntity
{
public:
  ProjectEntity();
  ~ProjectEntity();

public:
  void CreateProgram(std::string* header, std::string* cpp);

private:
  std::vector<ClassEntity*> class_entities_;

};
