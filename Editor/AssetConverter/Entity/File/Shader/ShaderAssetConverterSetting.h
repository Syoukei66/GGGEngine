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
  virtual bool EditWithImGuiProcess() override;

  // =================================================================
  // Data Members
  // =================================================================
public:
};

CEREAL_CLASS_VERSION(ShaderAssetConverterSetting, 0);
CEREAL_REGISTER_TYPE(ShaderAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, ShaderAssetConverterSetting);
