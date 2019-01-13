#pragma once

#include <Entity/AssetEntity.h>
#include "AssetProgramGenerator_namespace.h"
#include "AssetProgramGenerator_identifier.h"

class AssetProgramGenerator
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetProgramGenerator(const std::string& asset_name, const std::string& class_name, T_UINT32 skip_head, T_UINT32 skip_tail)
    : namespace_generator_()
    , identifier_generator_(skip_head, skip_tail)
  {
    this->AddAsset(asset_name, class_name);
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  void AddAsset(const std::string& asset_name, const std::string& class_name)
  {
    this->namespace_generator_.AddAsset(asset_name, class_name);
  }

  void CreateHeaderProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* dest)
  {
    (*dest).append(this->namespace_generator_.CreateHeaderProgram([&](const DefinitionGenerator& generator)
    {
      std::string str;
      for (const SharedRef<AssetEntity>& entity : entities)
      {
        str.append(generator.CreateHeaderProgram(this->identifier_generator_, entity->GetMetaData()));
      }
      return str;
    }));
  }
  void CreateCppProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* dest)
  {
    (*dest).append(this->namespace_generator_.CreateCppProgram([&](const DefinitionGenerator& generator)
    {
      std::string str;
      for (const SharedRef<AssetEntity>& entity : entities)
      {
        str.append(generator.CreateCppProgram(this->identifier_generator_, entity->GetMetaData()));
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