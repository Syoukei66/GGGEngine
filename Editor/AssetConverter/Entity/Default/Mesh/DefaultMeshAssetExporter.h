#pragma once

#include <Entity/AssetExporter.h>
#include "DefaultMeshAssetEntity.h"

class DefaultMeshAssetExporter : public AssetExporter<DefaultMeshAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(DefaultMeshAssetEntity* entity, const AssetConverterContext* context) override;

};
