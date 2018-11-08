#pragma once

#include <vector>
#include <functional>

#include "AssetProgramGenerator_definition.h"

class NamespaceGenerator
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NamespaceGenerator() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  inline void AddAsset(const std::string& asset_name, const std::string& class_name)
  {
    this->namespaces_.emplace_back(asset_name, class_name);
  }

  std::string CreateHeaderProgram(const std::function<std::string(const DefinitionGenerator&)>& func) const;
  std::string CreateCppProgram(const std::function<std::string(const DefinitionGenerator&)>& func) const;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<DefinitionGenerator> namespaces_;
};
