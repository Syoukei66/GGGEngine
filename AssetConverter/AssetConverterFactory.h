#pragma once

class IAssetConverter;

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
  virtual IAssetConverter* Create() const = 0;

};