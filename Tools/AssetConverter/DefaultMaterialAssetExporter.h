#pragma once

#include "AssetExporter.h"
#include "DefaultMaterialAssetEntity.h"

class DefaultMaterialAssetExporter : public AssetExporter<DefaultMaterialAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(DefaultMaterialAssetEntity* entity, const AssetConverterContext* context) override;

};
