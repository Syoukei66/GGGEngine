#pragma once

class AssetConverterContext;

class IAssetConverterAddIn
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief Converter�̓o�^
   * @param context
   */
  virtual void RegisterConverter(AssetConverterContext* context) = 0;

  /*!
   * @brief DefaultAsset�̓o�^
   * @param context
   */
  virtual void RegisterDefaultAsset(AssetConverterContext* context) = 0;

};