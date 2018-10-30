#include <stdio.h>
#include <iostream>
#include "ModuleEntity.h"

int main(int argc, char* argv[])
{
  std::vector<ModuleEntity*> modules;

  for (int i = 1; i < argc; ++i)
  {
    modules.emplace_back(
      (new ModuleEntity(argv[i]))
    );
  }

  for (const ModuleEntity* entity : modules)
  {
    entity->CreateHeaderProgram();
    delete entity;
  }

  std::cout << std::endl;
  getchar();
}