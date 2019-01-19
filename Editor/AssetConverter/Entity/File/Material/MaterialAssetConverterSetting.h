#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief MaterialAssetConverter�̐ݒ�
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
   * @brief �f�t�H���g�R���X�g���N�^�B�V���A���C�Y�p
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
