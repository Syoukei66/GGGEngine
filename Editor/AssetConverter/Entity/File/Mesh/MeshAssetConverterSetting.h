#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief MeshAssetConverter�̐ݒ�
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
    ar(cereal::base_class<ConverterSetting>(this));
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief �f�t�H���g�R���X�g���N�^�B�V���A���C�Y�p
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