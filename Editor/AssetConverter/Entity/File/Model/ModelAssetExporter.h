#pragma once

#include <Entity/AssetExporter.h>
#include "ModelAssetEntity.h"

class ModelAssetExporter : public AssetExporter<ModelAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(const SharedRef<ModelAssetEntity>& entity, const AssetConverterContext* context) override;

};
