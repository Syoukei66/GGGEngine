#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief DefaultMeshAssetConverter�̐ݒ�
 */
class DefaultAssetConverterSetting : public ConverterSetting
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
   * @brief �f�t�H���g�R���X�g���N�^�B�V���A���C�Y�p
   */
  DefaultAssetConverterSetting() = default;

  DefaultAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
  {}

  // =================================================================
  // Methods from ConverterSetting
  // =================================================================
protected:
  virtual bool EditWithImGuiProcess() override
  {
    return false;
  }

};

CEREAL_CLASS_VERSION(DefaultAssetConverterSetting, 0);
CEREAL_REGISTER_TYPE(DefaultAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, DefaultAssetConverterSetting);