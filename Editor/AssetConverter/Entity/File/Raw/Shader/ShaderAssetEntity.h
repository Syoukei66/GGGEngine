#pragma once

#include <Entity/File/Raw/RawAssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class ShaderAssetEntity : public RawAssetEntity<rcShader>
{
  ENTITY_ID(ID_SHADER);

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
    : RawAssetEntity(info)
  {}
};
