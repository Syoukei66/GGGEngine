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
    , is_master_()
    , edit_data_()
  {
    this->AddSubAsset(DefaultUniqueID::SHADER_ERRROR);
    this->AddSubAsset(DefaultUniqueID::TEXTURE_WHITE);
  }

  // =================================================================
  // Methods from ConverterSetting
  // =================================================================
protected:
  virtual bool EditWithImGuiProcess() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief �V�F�[�_�[����v���p�e�B���擾����
   */
  void StoreShaderProperties(const MaterialData& data);

  // =================================================================
  // Data Members
  // =================================================================
public:
  /*!
   * @brief �ŐV�̃f�[�^�������Ă��邩
   */
  bool is_master_;

  /*!
   * @brief �f�[�^���X�V���ꂽ��
   */
  bool is_updated_;
  MaterialData edit_data_;
};

CEREAL_CLASS_VERSION(MaterialAssetConverterSetting, 0);
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(MaterialAssetConverterSetting, cereal::specialization::member_load_save)