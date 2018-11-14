#pragma once

#include <Entity/AssetExporter.h>
#include "ModelMaterialAssetEntity.h"

class ModelMaterialAssetExporter : public AssetExporter<ModelMaterialAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(const SharedRef<ModelMaterialAssetEntity>& entity, const AssetConverterContext* context) override;

};
