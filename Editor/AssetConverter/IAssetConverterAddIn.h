#pragma once

class AssetConverterContext;

class IAssetConverterAddIn
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief Converter‚Ì“o˜^
   * @param context
   */
  virtual void RegisterConverter(AssetConverterContext* context) = 0;

  /*!
   * @brief DefaultAsset‚Ì“o˜^
   * @param context
   */
  virtual void RegisterDefaultAsset(AssetConverterContext* context) = 0;

};