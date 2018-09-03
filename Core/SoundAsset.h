#pragma once

#include "Asset.h"
#include "Sound.h"

class SoundAsset : public Asset<SoundAsset, rcSound>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  SoundAsset(const std::string& path)
    : Asset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcSound* LoadProcess(const std::string& path) override
  {
    return rcSound::LoadProcess(path.c_str());
  }

};