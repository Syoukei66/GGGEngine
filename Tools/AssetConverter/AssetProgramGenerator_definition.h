#pragma once

#include <string>

#include "AssetInfo.h"
#include "AssetProgramGenerator_identifier.h"

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
  std::string CreateHeaderProgram(const IdentifierGenerator& id_generator, const AssetInfo* info) const;
  std::string CreateCppProgram(const IdentifierGenerator& id_generator, const AssetInfo* info) const;
  std::string CreateTypeName() const;
  std::string CreateTypeNameAlias() const;
  std::string CreateLoaderNameAlias() const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE const std::string& GetAssetName() const
  {
    return this->asset_name_;
  }

  GG_INLINE const std::string& GetClassName() const
  {
    return this->class_name_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string asset_name_;
  std::string class_name_;
  T_UINT32 skip_head_;
  T_UINT32 skip_tail_;

};

