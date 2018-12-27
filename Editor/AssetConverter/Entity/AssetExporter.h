#pragma once

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
  void Export(const std::unordered_map<T_UINT32, SharedRef<AssetEntity>>& entities, const AssetConverterContext* context);

protected:
  virtual void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) = 0;

};
