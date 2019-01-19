#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief TextureAssetConverter�̐ݒ�
 */
class TextureAssetConverterSetting : public ConverterSetting
{
public:
  enum class ColorModel : T_FIXED_UINT8
  {
    kRGB,
    kRGBA,
    kHDR,

    kDataNum,
  };

  enum class CompressionQuality : T_FIXED_UINT8
  {
    kNone,
    kNormal,
    kHigh,
    kLow,

    kDataNum
  };

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(CEREAL_NVP(max_size));
    ar(CEREAL_NVP(compression));
    ar(CEREAL_NVP(color_model));
    ar(CEREAL_NVP(view_data));
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief �f�t�H���g�R���X�g���N�^�B�V���A���C�Y�p
   */
  TextureAssetConverterSetting() = default;

  TextureAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
    , max_size(2048)
    , compression(static_cast<T_FIXED_UINT8>(CompressionQuality::kNormal))
    , color_model(static_cast<T_FIXED_UINT8>(ColorModel::kRGBA))
    , view_data()
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
  T_FIXED_UINT16 max_size;
  T_FIXED_UINT8 compression; // Compression
  T_FIXED_UINT8 color_model; // ColorModel
  TextureViewData view_data;
};

CEREAL_CLASS_VERSION(TextureAssetConverterSetting, 0);
CEREAL_REGISTER_TYPE(TextureAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, TextureAssetConverterSetting);
