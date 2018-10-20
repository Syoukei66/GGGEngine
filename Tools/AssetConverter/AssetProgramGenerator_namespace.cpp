#include "AssetProgramGenerator_namespace.h"

// =================================================================
// Methods
// =================================================================
std::string NamespaceGenerator::CreateHeaderProgram(const std::function<std::string(const DefinitionGenerator&)>& func) const
{
  std::string ret;
  for (const DefinitionGenerator& generator : this->namespaces_)
  {
    ret.append("namespace " + generator.GetAssetName() + "\n");
    ret.append("{\n");
    ret.append("using " + generator.CreateTypeNameAlias() + " = " + generator.CreateTypeName() + ";\n");
    ret.append("using " + generator.CreateLoaderNameAlias() + " = const AssetLoader<" + generator.CreateTypeNameAlias() + ">&;\n");
    ret.append(func(generator));
    ret.append("}; // namespace " + generator.GetAssetName() + "\n");
    ret.append("\n");
  }
  return ret;
}

std::string NamespaceGenerator::CreateCppProgram(const std::function<std::string(const DefinitionGenerator&)>& func) const
{
  std::string ret;
  for (const DefinitionGenerator& generator : this->namespaces_)
  {
    ret.append("namespace " + generator.GetAssetName() + "\n");
    ret.append("{\n");
    ret.append(func(generator));
    ret.append("}; // namespace " + generator.GetAssetName() + "\n");
    ret.append("\n");
  }
  return ret;
}
