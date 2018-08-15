#pragma once

#include <vector>

#include "AssetProgramGenerator_definition.h"

namespace AssetProgram
{

class NamespaceGenerator
{
public:
  NamespaceGenerator() = default;

public:
  inline void AddAsset(const std::string& asset_name, const std::string& class_name)
  {
    this->namespaces_.emplace_back(asset_name, class_name);
  }

public:
  std::string CreateHeaderProgram(const std::function<std::string(const DefinitionGenerator&)>& func) const;
  std::string CreateCppProgram(const std::function<std::string(const DefinitionGenerator&)>& func) const;

private:
  std::vector<DefinitionGenerator> namespaces_;
};

}

