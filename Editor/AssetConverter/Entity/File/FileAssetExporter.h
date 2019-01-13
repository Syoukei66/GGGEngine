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
  void ExportProcess(AssetMetaData* meta_data, void* mid_data, const AssetConverterContext* context) override
  {
    CerealIO::Binary::Export(meta_data->GetOutputPath().c_str(), (AssetData_*)mid_data);
    Logger::ConvertAssetLog(meta_data);
  }

};