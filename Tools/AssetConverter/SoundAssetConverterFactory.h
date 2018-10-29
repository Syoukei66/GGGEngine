#pragma once

#include "AssetEntity.h"
#include "RawAssetConverterFactory.h"

class SoundAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_SOUND)
public:
  static GG_INLINE IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<SoundAssetEntity>("Sound", "rcSound", "wav");
  }
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SoundAssetEntity(AssetInfo* info)
    : AssetEntity(info)
  {}
};
