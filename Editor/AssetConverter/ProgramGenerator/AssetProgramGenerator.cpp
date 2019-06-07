#include "AssetProgramGenerator.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AssetProgramGenerator::AssetProgramGenerator(const std::string & asset_name, const std::string & class_name, T_UINT32 skip_head, T_UINT32 skip_tail)
  : namespace_generator_()
  , identifier_generator_(skip_head, skip_tail)
{
  this->AddAsset(asset_name, class_name);
}

// =================================================================
// Methods
// =================================================================
void AssetProgramGenerator::AddAsset(const std::string & asset_name, const std::string & class_name)
{
  this->namespace_generator_.AddAsset(asset_name, class_name);
}

void AssetProgramGenerator::CreateHeaderProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string * dest)
{
  (*dest).append(this->namespace_generator_.CreateHeaderProgram([&](const DefinitionGenerator& generator)
  {
    std::string str;
    for (const SharedRef<AssetEntity>& entity : entities)
    {
      str.append(generator.CreateHeaderProgram(this->identifier_generator_, entity->GetMetaData()));
    }
    return str;
  }));
}

void AssetProgramGenerator::CreateCppProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string * dest)
{
  (*dest).append(this->namespace_generator_.CreateCppProgram([&](const DefinitionGenerator& generator)
  {
    std::string str;
    for (const SharedRef<AssetEntity>& entity : entities)
    {
      str.append(generator.CreateCppProgram(this->identifier_generator_, entity->GetMetaData()));
    }
    return str;
  }));
}
