#include <stdio.h>
#include "ModuleEntity.h"

int main()
{
  std::vector<ModuleEntity*> modules;

  modules.emplace_back(
    (new ModuleEntity("Core"))
  );

  modules.emplace_back(
    (new ModuleEntity("Engine"))
    ->AddSpecial("Core/Include.h")
  );

  for (const ModuleEntity* entity : modules)
  {
    entity->CreateHeaderProgram();
    delete entity;
  }
}