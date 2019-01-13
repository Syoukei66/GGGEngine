#pragma once

class AssetConverter;
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
  virtual AssetConverter* Create(AssetConverterContext* context) const = 0;

};