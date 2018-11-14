#pragma once

#include <Entity/File/Raw/RawAssetEntity.h>
#include <Entity/File/Raw/RawAssetConverterFactory.h>

class SoundAssetEntity : public RawAssetEntity<rcAudioClip>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_SOUND);
  GG_OBJECT(SoundAssetEntity);
  GG_CREATE_FUNC_1(SoundAssetEntity, AssetInfo*)
  {
    return AssetEntity::Init(arg0);
  }

public:
  static inline IAssetConverter* CreateConverter()
  {
    return RawAssetConverterFactory::Create<SoundAssetEntity>("Sound", "rcAudioClip", "wav");
  }

};
