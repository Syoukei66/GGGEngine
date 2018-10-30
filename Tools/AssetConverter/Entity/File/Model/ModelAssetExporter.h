#pragma once

#include <Entity/AssetExporter.h>
#include "ModelAssetEntity.h"

class ModelAssetExporter : public AssetExporter<ModelAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(ModelAssetEntity* entity, const AssetConverterContext* context) override;

};
