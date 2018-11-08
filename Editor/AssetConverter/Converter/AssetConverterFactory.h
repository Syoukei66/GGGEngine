#pragma once

class IAssetConverter;
class AssetConverterContext;

class AssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterFactory() = default;
  virtual ~AssetConverterFactory() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual IAssetConverter* Create(AssetConverterContext* context) const = 0;

};