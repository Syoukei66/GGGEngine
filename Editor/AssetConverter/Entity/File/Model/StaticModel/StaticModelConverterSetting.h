#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief StaticModelAssetConverterの設定
 */
class StaticModelAssetConverterSetting : public ConverterSetting
{
  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(CEREAL_NVP(scale));
    ar(CEREAL_NVP(override_material));
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief デフォルトコンストラクタ。シリアライズ用
   */
  StaticModelAssetConverterSetting() = default;

  StaticModelAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
    , scale(1.0f)
    , override_material(true)
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
  T_FLOAT scale;
  bool override_material;

};

CEREAL_CLASS_VERSION(StaticModelAssetConverterSetting, 0);
CEREAL_REGISTER_TYPE(StaticModelAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, StaticModelAssetConverterSetting);
