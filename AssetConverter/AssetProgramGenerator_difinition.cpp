#include "AssetProgramGenerator_difinition.h"

AssetProgram::DefinitionGenerator::DefinitionGenerator(const std::string& asset_name, const std::string& class_name)
  : asset_name_(asset_name)
  , class_name_(class_name)
{
}

AssetProgram::DefinitionGenerator::~DefinitionGenerator()
{
}

static std::string CreateFilePath(AssetInfo* info)
{
  return std::to_string(info->meta_data->unique_id) + "." + info->extension;
}

std::string AssetProgram::DefinitionGenerator::CreateHeaderProgram(AssetInfo* info) const
{
  return "extern " + this->CreateTypeName() + " " + info->program_id + ";\n";
}

std::string AssetProgram::DefinitionGenerator::CreateCppProgram(AssetInfo* info) const
{
  return this->CreateTypeName() + " " + info->program_id + "(\"" + CreateFilePath(info) + "\");\n";
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
