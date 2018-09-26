#pragma once

#include "AssetEditor.h"
#include "ModelAssetEntity.h"

class ModelAssetEditor : public AssetEditor<ModelAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void Edit(ModelAssetEntity* entity) override;

};
