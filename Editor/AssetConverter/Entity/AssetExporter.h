#pragma once

class AssetMetaData;
class AssetConverterContext;

class AssetExporter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetExporter() = default;
  virtual ~AssetExporter() = default;
 
  // =================================================================
  // Methods
  // =================================================================
public:
  void Export(AssetMetaData* meta_data, void* mid_data, const AssetConverterContext* context);

protected:
  virtual void ExportProcess(AssetMetaData* meta_data, void* mid_data, const AssetConverterContext* context) = 0;

};
