#pragma once

#include "AssetExporter.h"
#include "ModelMaterialAssetEntity.h"

class ModelMaterialAssetExporter : public AssetExporter<ModelMaterialAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(ModelMaterialAssetEntity* entity, const AssetConverterContext* context) override;

};
