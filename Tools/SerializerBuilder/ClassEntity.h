#pragma once

#include <vector>
#include "VariableEntity.h"

class ClassEntity
{
public:
  ClassEntity();
  ~ClassEntity();

public:
  void CreateProgram(std::string* header, std::string* cpp);

private:
  std::vector<VariableEntity*> class_entities_;

};
