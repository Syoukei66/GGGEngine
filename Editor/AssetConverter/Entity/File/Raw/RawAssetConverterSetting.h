#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief RawAssetConverterの設定
 */
class RawAssetConverterSetting : public ConverterSetting
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
  RawAssetConverterSetting() = default;

  RawAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
  {}

  // =================================================================
  // Methods from ConverterSetting
  // =================================================================
protected:
  virtual bool EditWithImGuiProcess() override;

};

CEREAL_CLASS_VERSION(RawAssetConverterSetting, 0);
CEREAL_REGISTER_TYPE(RawAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, RawAssetConverterSetting);

