#pragma once

#include <Entity/AssetExporter.h>
#include <Core/_Private/CerealIO.h>

template <class AssetData_>
class FileAssetExporter : public AssetExporter
{
  // =================================================================
  // Methods
  // =================================================================
protected:
  void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) override
  {
    AssetMetaData* meta_data = entity->GetMetaData();
    CerealIO::Binary::Export<AssetData_>(meta_data->GetOutputPath().c_str(), (AssetData_*)entity->GetData());
    Logger::ConvertAssetLog(meta_data);
  }

};