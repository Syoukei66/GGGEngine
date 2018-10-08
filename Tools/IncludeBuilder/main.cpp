#include <stdio.h>
#include <iostream>
#include "ModuleEntity.h"

int main()
{
  std::vector<ModuleEntity*> modules;

  modules.emplace_back(
    (new ModuleEntity("Core"))
  );

  modules.emplace_back(
    (new ModuleEntity("ThirdParty/imgui"))
  );

  modules.emplace_back(
    (new ModuleEntity("Engine"))
    ->AddSpecial("Core/Include.h")
    ->AddSpecial("ThirdParty/imgui/Include.h")
  );

  for (const ModuleEntity* entity : modules)
  {
    entity->CreateHeaderProgram();
    delete entity;
  }

  std::cout << std::endl;
  getchar();
}