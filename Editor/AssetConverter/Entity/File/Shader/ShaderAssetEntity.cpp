#include "ShaderAssetEntity.h"
#include "ShaderAssetImporter.h"

IAssetConverter* ShaderAssetEntity::CreateConverter()
{
  return FileAssetConverterFactory::Create<ShaderAssetEntity>(
    new ShaderAssetImporter({ "shader" }),
    "Shader",
    "rcShader",
    1,
    1
    );
}
