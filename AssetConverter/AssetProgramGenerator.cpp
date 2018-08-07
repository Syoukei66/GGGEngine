#include "AssetProgramGenerator.h"

AssetProgram::Generator::Generator()
{

}

void AssetProgram::Generator::Generate(const AssetManager& asset_manager, std::string* header, std::string* cpp)
{
  //======================================
  //Asset.h
  //======================================
  header->append("#pragma once\n");
  header->append("#include <" + asset_manager.GetSetting()->engine_name + ".h>\n");
  std::set<std::string> includes = std::set<std::string>();
  asset_manager.VisitConverter([&](const BaseConverter* converter)
  {
    converter->GetIncludePaths(&includes);
  });
  for (const std::string& include : includes)
  {
    header->append("#include \"" + include + "\"\n");
  }
  header->append("\n");
  header->append("namespace Asset\n");
  header->append("{\n");
  header->append("\n");

  asset_manager.VisitConverter([&](const BaseConverter* converter)
  {
    header->append(converter->CreateHeaderProgram());
  });

  header->append("} // namespace Asset\n");

  //======================================
  //Asset.cpp
  //======================================

  //cpp head
  cpp->append("#include \"Asset.h\"\n");
  cpp->append("\n");
  cpp->append("namespace Asset\n");
  cpp->append("{\n");
  cpp->append("\n");

  //Body
  asset_manager.VisitConverter([&](const BaseConverter* converter)
  {
    cpp->append(converter->CreateCppProgram());
  });

  //cpp bottom
  cpp->append("} // namespace Asset\n");

  asset_manager.VisitConverter([&](const BaseConverter* converter)
  {
    converter->Convert();
  });
}

