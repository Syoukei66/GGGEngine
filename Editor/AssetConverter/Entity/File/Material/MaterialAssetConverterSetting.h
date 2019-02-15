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
  void save(Archive& ar, std::uint32_t const version) const
  {
    ar(cereal::base_class<ConverterSetting>(this));
  }

  template<class Archive>
  void load(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::base_class<ConverterSetting>(this));
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
  {
  }

  // =================================================================
  // Methods from ConverterSetting
  // =================================================================
protected:
  virtual bool EditWithImGuiProcess(AssetConverterContext* context) override;

};

CEREAL_CLASS_VERSION(MaterialAssetConverterSetting, 0);
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(MaterialAssetConverterSetting, cereal::specialization::member_load_save)