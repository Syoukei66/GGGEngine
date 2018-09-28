#pragma once

#include <string>

#include "AssetInfo.h"

class DefinitionGenerator
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefinitionGenerator(const std::string& asset_name, const std::string& class_name);
  ~DefinitionGenerator();

  // =================================================================
  // Methods
  // =================================================================
public:
  std::string CreateHeaderProgram(const AssetInfo* info) const;
  std::string CreateCppProgram(const AssetInfo* info) const;
  std::string CreateTypeName() const;
  std::string CreateTypeNameAlias() const;
  std::string CreateContainerNameAlias() const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const std::string& GetAssetName() const
  {
    return this->asset_name_;
  }

  inline const std::string& GetClassName() const
  {
    return this->class_name_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string asset_name_;
  std::string class_name_;
};

