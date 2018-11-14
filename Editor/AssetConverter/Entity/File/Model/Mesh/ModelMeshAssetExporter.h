#pragma once

#include <Entity/AssetExporter.h>
#include "ModelMeshAssetEntity.h"

class ModelMeshAssetExporter : public AssetExporter<ModelMeshAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(const SharedRef<ModelMeshAssetEntity>& entity, const AssetConverterContext* context) override;

};
