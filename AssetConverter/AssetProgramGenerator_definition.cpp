#include "AssetProgramGenerator_definition.h"

AssetProgram::DefinitionGenerator::DefinitionGenerator(const std::string& asset_name, const std::string& class_name)
  : asset_name_(asset_name)
  , class_name_(class_name)
{
}

AssetProgram::DefinitionGenerator::~DefinitionGenerator()
{
}

std::string AssetProgram::DefinitionGenerator::CreateHeaderProgram(AssetInfo* info) const
{
  return "extern " + this->CreateContainerNameAlias() + " " + info->program_id + ";\n";
}

std::string AssetProgram::DefinitionGenerator::CreateCppProgram(AssetInfo* info) const
{
  return this->CreateContainerNameAlias() + " " + info->program_id  + " = " + "OldAssetManager::GetInstance().Register<" + this->CreateTypeNameAlias() + ">(" + std::to_string(info->meta_data->unique_id) + ", \"" + info->extension + "\");\n";
}

std::string AssetProgram::DefinitionGenerator::CreateTypeName() const
{
  std::string type_name = std::string();

  if (this->asset_name_ == this->class_name_)
  {
    type_name.append("class ");
  }
  type_name.append(this->class_name_);

  return type_name;
}

std::string AssetProgram::DefinitionGenerator::CreateTypeNameAlias() const
{
  return "T_";
}

std::string AssetProgram::DefinitionGenerator::CreateContainerNameAlias() const
{
  return "Cont_";
}
