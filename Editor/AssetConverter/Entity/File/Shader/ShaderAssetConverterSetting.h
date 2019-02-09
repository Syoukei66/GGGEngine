#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief ShaderAssetConverter�̐ݒ�
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
    ar(cereal::base_class<ConverterSetting>(this));
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:

  /*!
 * @brief �f�t�H���g�R���X�g���N�^�B�V���A���C�Y�p
 */
  ShaderAssetConverterSetting() = default;

  ShaderAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
  {}

  // =================================================================
  // Methods from ConverterSetting
  // =================================================================
protected:
  virtual bool EditWithImGuiProcess(AssetConverterContext* context) override;

  // =================================================================
  // Data Members
  // =================================================================
public:
};

CEREAL_CLASS_VERSION(ShaderAssetConverterSetting, 0);
