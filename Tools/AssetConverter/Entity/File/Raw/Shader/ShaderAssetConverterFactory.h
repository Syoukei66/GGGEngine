#pragma once

#include <Entity/AssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class ShaderAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_SHADER)
public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<ShaderAssetEntity>("Shader", "rcShader", "cso");
  }
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ShaderAssetEntity(AssetInfo* info)
    : AssetEntity(info)
  {}
};
