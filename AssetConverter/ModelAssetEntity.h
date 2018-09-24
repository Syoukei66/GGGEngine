#pragma once

#include "AssetEntity.h"

class ModelAssetEntity : public AssetEntity
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelAssetEntity(AssetInfo* info)
    : AssetEntity(info)
  {
  }

};