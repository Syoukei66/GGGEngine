#pragma once

#include <Entity/AssetExporter.h>
#include <Util/FileUtil.h>

class RawAssetExporter : public AssetExporter
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) override
  {
    FileUtil::CopyRawAsset(entity->GetMetaData());
  }

};
