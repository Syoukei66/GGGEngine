#pragma once

#include <Entity/File/Raw/RawAssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class SoundAssetEntity : public RawAssetEntity<rcAudioClip>
{
  ENTITY_ID(ID_SOUND)

public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<SoundAssetEntity>("Sound", "rcAudioClip", "wav");
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SoundAssetEntity(AssetInfo* info)
    : RawAssetEntity(info)
  {}
};
