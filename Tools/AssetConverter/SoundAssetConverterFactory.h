#pragma once

#include "AssetEntity.h"
#include "RawAssetConverterFactory.h"

class SoundAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_SOUND)
public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<SoundAssetEntity>("Sound", "SoundAsset", "wav");
  }
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SoundAssetEntity(AssetInfo* info)
    : AssetEntity(info)
  {}
};
