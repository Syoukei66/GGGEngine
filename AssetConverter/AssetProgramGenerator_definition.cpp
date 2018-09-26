#include "AssetProgramGenerator_definition.h"

DefinitionGenerator::DefinitionGenerator(const std::string& asset_name, const std::string& class_name)
  : asset_name_(asset_name)
  , class_name_(class_name)
{
}

DefinitionGenerator::~DefinitionGenerator()
{
}

std::string DefinitionGenerator::CreateHeaderProgram(const AssetInfo* info) const
{
  return "extern " + this->CreateContainerNameAlias() + " " + info->GetProgramID() + ";\n";
}

std::string DefinitionGenerator::CreateCppProgram(const AssetInfo* info) const
{
  return this->CreateContainerNameAlias() + " " + info->GetProgramID() + " = " + "Director::GetInstance().Register<" + this->CreateTypeNameAlias() + ">(" + std::to_string(info->GetUniqueID()) + ", \"" + info->GetURI().GetExtension() + "\");\n";
}

std::string DefinitionGenerator::CreateTypeName() const
{
  std::string type_name = std::string();

  if (this->asset_name_ == this->class_name_)
  {
    type_name.append("class ");
  }
  type_name.append(this->class_name_);

  return type_name;
}

std::string DefinitionGenerator::CreateTypeNameAlias() const
{
  return "T_";
}

std::string DefinitionGenerator::CreateContainerNameAlias() const
{
  return "Cont_";
}
