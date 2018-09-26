#pragma once

#include "AssetExporter.h"
#include "ModelMeshAssetEntity.h"

class ModelMeshAssetExporter : public AssetExporter<ModelMeshAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(ModelMeshAssetEntity* entity, const AssetConverterContext* context) override;

};
