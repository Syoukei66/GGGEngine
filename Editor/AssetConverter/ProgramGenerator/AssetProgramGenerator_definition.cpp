#include "AssetProgramGenerator_definition.h"

DefinitionGenerator::DefinitionGenerator(const std::string& asset_name, const std::string& class_name)
  : asset_name_(asset_name)
  , class_name_(class_name)
{
}

DefinitionGenerator::~DefinitionGenerator()
{
}

std::string DefinitionGenerator::CreateHeaderProgram(const IdentifierGenerator& id_generator, const AssetMetaData* meta) const
{
  return "extern " + this->CreateLoaderNameAlias() + " " + id_generator.CreateIdentifier(meta) + ";\n";
}

std::string DefinitionGenerator::CreateCppProgram(const IdentifierGenerator& id_generator, const AssetMetaData* meta) const
{
  return this->CreateLoaderNameAlias() + " " + id_generator.CreateIdentifier(meta) + " = " + "AssetManager::AddAsset<" + this->CreateTypeNameAlias() + ">(" + std::to_string(meta->GetUniqueID()) + ", \"" + meta->GetURI().GetExtension() + "\");\n";
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

std::string DefinitionGenerator::CreateLoaderNameAlias() const
{
  return "Cont_";
}
