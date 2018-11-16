#pragma once

#include <Entity/AssetExporter.h>
#include "StaticModelAssetEntity.h"

class StaticModelAssetExporter : public AssetExporter<StaticModelAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(const SharedRef<StaticModelAssetEntity>& entity, const AssetConverterContext* context) override;

};
