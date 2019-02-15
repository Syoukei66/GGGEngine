#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief ShaderAssetConverterの設定
 */
class ShaderAssetConverterSetting : public ConverterSetting
{
  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::base_class<ConverterSetting>(this));
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:

  /*!
 * @brief デフォルトコンストラクタ。シリアライズ用
 */
  ShaderAssetConverterSetting() = default;

  ShaderAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
  {}

  // =================================================================
  // Methods from ConverterSetting
  // =================================================================
protected:
  virtual bool EditWithImGuiProcess(AssetConverterContext* context) override;

  // =================================================================
  // Data Members
  // =================================================================
public:
};

CEREAL_CLASS_VERSION(ShaderAssetConverterSetting, 0);
