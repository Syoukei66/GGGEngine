#pragma once

#include <string>
#include "AssetProgramGenerator_namespace.h"
#include "AssetProgramGenerator_identifier.h"

template <class Entity_>
class AssetProgramGenerator
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetProgramGenerator(T_UINT32 skip_head, T_UINT32 skip_tail)
    : namespace_generator_()
    , identifier_generator_(skip_head, skip_tail)
  {
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  void AddAsset(const std::string& asset_name, const std::string& class_name)
  {
    this->namespace_generator_.AddAsset(asset_name, class_name);
  }

  void CreateHeaderProgram(const std::unordered_map<T_UINT32, Entity_*>& entities, std::string* dest)
  {
    (*dest).append(this->namespace_generator_.CreateHeaderProgram([&](const DefinitionGenerator& generator)
    {
      std::string str;
      for (auto& pair : entities)
      {
        str.append(generator.CreateHeaderProgram(this->identifier_generator_, pair.second->GetAssetInfo()));
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
        str.append(generator.CreateCppProgram(this->identifier_generator_, pair.second->GetAssetInfo()));
      }
      return str;
    }));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  NamespaceGenerator namespace_generator_;
  IdentifierGenerator identifier_generator_;

};