#pragma once

#include "AssetEntity.h"

class RawAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_RAW)
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RawAssetEntity(AssetInfo* info)
    : AssetEntity(info)
  {
  }

};