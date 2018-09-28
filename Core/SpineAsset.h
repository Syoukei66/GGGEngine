#pragma once

#include "Asset.h"
#include "SpineData.h"

class SpineAsset : public BaseAsset<SpineAsset, rcSpineData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  SpineAsset(const std::string& path)
    : BaseAsset(path)
  {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  rcSpineData* LoadProcess(const std::string& path) override
  {
    return rcSpineData::LoadProcess(path.c_str());
  }

};