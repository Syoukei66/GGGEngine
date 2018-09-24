#pragma once

#include "AssetExporter.h"
#include "RawAssetEntity.h"

class RawAssetExporter : public AssetExporter<RawAssetEntity>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(RawAssetEntity* entity, const AssetConverterContext* context) override;
};
