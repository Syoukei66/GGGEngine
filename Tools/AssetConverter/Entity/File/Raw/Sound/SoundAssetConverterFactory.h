#pragma once

#include <Entity/AssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class SoundAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_SOUND)
public:
  static inline IAssetConverter* CreateConverter()
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
