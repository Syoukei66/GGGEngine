#pragma once

#include <Entity/AssetExporter.h>
#include <Util/FileUtil.h>

template <class Entity_>
class RawAssetExporter : public AssetExporter<Entity_>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(Entity_* entity, const AssetConverterContext* context) override
  {
    FileUtil::CopyRawAsset(entity->GetAssetInfo());
  }

};
