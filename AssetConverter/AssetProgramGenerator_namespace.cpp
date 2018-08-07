#include "AssetProgramGenerator_namespace.h"

std::string AssetProgram::NamespaceGenerator::CreateProgram(const std::function<std::string(const DefinitionGenerator&)>& func) const
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
