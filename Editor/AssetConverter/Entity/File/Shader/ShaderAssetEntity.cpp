#include "ShaderAssetEntity.h"
#include "ShaderAssetImporter.h"

IAssetConverter* ShaderAssetEntity::CreateConverter()
{
  return FileAssetConverterFactory::Create<ShaderAssetEntity>(
    new ShaderAssetImporter({ "fx" }),
    "Shader",
    "rcShader",
    1,
    1
    );
}
