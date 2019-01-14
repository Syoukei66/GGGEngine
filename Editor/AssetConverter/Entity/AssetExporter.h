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
  void Export(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context);

protected:
  virtual void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) = 0;

};
