#pragma once

#include "AssetEditor.h"
#include "RawAssetEntity.h"

class RawAssetEditor : public AssetEditor<RawAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void Edit(RawAssetEntity* entity) override;

};
