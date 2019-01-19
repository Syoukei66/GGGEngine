#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief MeshAssetConverterの設定
 */
class MeshAssetConverterSetting : public ConverterSetting
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
  MeshAssetConverterSetting() = default;

  MeshAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
  {}

  // =================================================================
  // Methods from ConverterSetting
  // =================================================================
protected:
  virtual bool EditWithImGuiProcess() override;

};

CEREAL_CLASS_VERSION(MeshAssetConverterSetting, 0);
CEREAL_REGISTER_TYPE(MeshAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, MeshAssetConverterSetting);
