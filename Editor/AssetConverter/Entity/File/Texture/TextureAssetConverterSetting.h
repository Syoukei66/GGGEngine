#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief TextureAssetConverterの設定
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

  static const T_INT32 SELECTED_SIZE_INIT = 9;
  static const T_INT32 COMPRESSION_INIT = static_cast<T_FIXED_UINT8>(CompressionQuality::kNormal);
  static const T_INT32 COLOR_MODEL_INIT = static_cast<T_FIXED_UINT8>(ColorModel::kRGBA);

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::base_class<ConverterSetting>(this));
    ar(CEREAL_NVP(max_size));
    ar(CEREAL_NVP(compression));
    ar(CEREAL_NVP(color_model));
    ar(CEREAL_NVP(view_data));
    this->selected_size = SELECTED_SIZE_INIT;
    this->selected_compression = COMPRESSION_INIT;
    this->selected_color_model = COLOR_MODEL_INIT;
    this->selected_filter = this->view_data.filter_;
    this->selected_address = this->view_data.address_u_;
    this->selected_aniso_level = this->view_data.aniso_level_;
    this->selected_fade_start = this->view_data.fade_start_;
    this->selected_fade_end = this->view_data.fade_end_;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief デフォルトコンストラクタ。シリアライズ用
   */
  TextureAssetConverterSetting() = default;

  TextureAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
    , max_size(2048)
    , compression(COMPRESSION_INIT)
    , color_model(COLOR_MODEL_INIT)
    , view_data()
  {
    this->selected_size = SELECTED_SIZE_INIT;
    this->selected_compression = COMPRESSION_INIT;
    this->selected_color_model = COLOR_MODEL_INIT;
    this->selected_filter = this->view_data.filter_;
    this->selected_address = this->view_data.address_u_;
    this->selected_aniso_level = this->view_data.aniso_level_;
    this->selected_fade_start = this->view_data.fade_start_;
    this->selected_fade_end = this->view_data.fade_end_;
  }

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

  // Imgui用変数
  T_INT32 selected_size;
  T_INT32 selected_compression;
  T_INT32 selected_color_model;
  T_INT32 selected_filter;
  T_INT32 selected_address;
  T_INT32 selected_aniso_level;
  T_INT32 selected_fade_start;
  T_INT32 selected_fade_end;
};

CEREAL_CLASS_VERSION(TextureAssetConverterSetting, 0);
