#pragma once

#include <string>
#include "AssetProgramGenerator_namespace.h"

template <class Entity_>
class AssetProgramGenerator
{
public:
  AssetProgramGenerator() = default;

public:
  void CreateHeaderProgram(const std::unordered_map<T_UINT32, Entity_*>& entities, std::string* dest)
  {
    (*dest).append(this->namespace_generator_.CreateHeaderProgram([&](const DefinitionGenerator& generator)
    {
      std::string str;
      for (auto& pair : entities)
      {
        str.append(generator.CreateHeaderProgram(pair.second->GetInfo()));
      }
      return str;
    }));
  }
  void CreateCppProgram(const std::unordered_map<T_UINT32, Entity_*>& entities, std::string* dest)
  {
    (*dest).append(this->namespace_generator_.CreateCppProgram([&](const DefinitionGenerator& generator)
    {
      std::string str;
      for (auto& pair : entities)
      {
        str.append(generator.CreateCppProgram(pair.second->GetInfo()));
      }
      return str;
    }));
  }

private:
  NamespaceGenerator namespace_generator_;

};