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
  AssetProgramGenerator(const std::string& asset_name, const std::string& class_name, T_UINT32 skip_head, T_UINT32 skip_tail);

  // =================================================================
  // Methods
  // =================================================================
public:
  void AddAsset(const std::string& asset_name, const std::string& class_name);

  void CreateHeaderProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* dest);
  void CreateCppProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* dest);

  // =================================================================
  // Data Members
  // =================================================================
private:
  NamespaceGenerator namespace_generator_;
  IdentifierGenerator identifier_generator_;

};