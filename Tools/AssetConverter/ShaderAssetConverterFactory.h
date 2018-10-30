#pragma once

#include "AssetEntity.h"
#include "RawAssetConverterFactory.h"

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
