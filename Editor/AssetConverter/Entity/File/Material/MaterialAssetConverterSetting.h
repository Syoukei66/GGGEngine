#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief MaterialAssetConverterの設定
 */
class MaterialAssetConverterSetting : public ConverterSetting
{
  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(CEREAL_NVP(data));
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief デフォルトコンストラクタ。シリアライズ用
   */
  MaterialAssetConverterSetting() = default;

  MaterialAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
    , data()
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
  MaterialData data;
};

CEREAL_CLASS_VERSION(MaterialAssetConverterSetting, 0);
CEREAL_REGISTER_TYPE(MaterialAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, MaterialAssetConverterSetting);
