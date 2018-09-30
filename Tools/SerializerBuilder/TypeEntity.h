#pragma once

#include <vector>
#include "VariableEntity.h"

class TypeEntity
{
public:
  TypeEntity();
  ~TypeEntity();

public:
  void CreateProgram(std::string* header, std::string* cpp);

private:
  std::vector<VariableEntity*> type_entities_;

};
