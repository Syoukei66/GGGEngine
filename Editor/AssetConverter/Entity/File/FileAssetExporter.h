#pragma once

#include <Entity/AssetExporter.h>
#include <Core/_Private/CerealIO.h>

template <class Entity_>
class FileAssetExporter : public AssetExporter<Entity_>
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(const SharedRef<Entity_>& entity, const AssetConverterContext* context) override
  {
    CerealIO::Binary::Export(entity->GetMetaData()->GetOutputPath().c_str(), entity->GetData());
    Logger::ConvertAssetLog(entity->GetMetaData());
  }

};