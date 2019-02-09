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
    ar(CEREAL_NVP(convert_normal_map));
    ar(CEREAL_NVP(normal_scaling_factor));
    this->selected_size = (T_UINT16)std::log2(max_size) - 2;
    this->selected_compression = compression;
    this->selected_color_model = color_model;
    this->selected_filter = this->view_data.filter_;
    this->selected_address = this->view_data.address_u_;
    this->selected_fade_enabled = this->view_data.fade_enabled_;
    this->selected_aniso_level = this->view_data.aniso_level_;
    this->selected_fade_start = this->view_data.fade_start_;
    this->selected_fade_end = this->view_data.fade_end_;
    this->selected_convert_normal_map = this->convert_normal_map;
    this->selected_normal_scaling_factor = this->normal_scaling_factor;
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
    , compression(static_cast<T_FIXED_UINT8>(CompressionQuality::kNormal))
    , color_model(static_cast<T_FIXED_UINT8>(ColorModel::kRGBA))
    , view_data()
    , convert_normal_map()
    , normal_scaling_factor(1.0f)    
  {
    this->selected_size = (T_UINT16)std::log2(max_size) - 2;
    this->selected_compression = compression;
    this->selected_color_model = color_model;
    this->selected_filter = this->view_data.filter_;
    this->selected_address = this->view_data.address_u_;
    this->selected_fade_enabled = this->view_data.fade_enabled_;
    this->selected_aniso_level = this->view_data.aniso_level_;
    this->selected_fade_start = this->view_data.fade_start_;
    this->selected_fade_end = this->view_data.fade_end_;
    this->selected_convert_normal_map = this->convert_normal_map;
    this->selected_normal_scaling_factor = this->normal_scaling_factor;
  }

  // =================================================================
  // Methods from ConverterSetting
  // =================================================================
protected:
  virtual bool EditWithImGuiProcess(AssetConverterContext* context) override;

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT16 max_size;
  T_FIXED_UINT8 compression; // Compression
  T_FIXED_UINT8 color_model; // ColorModel
  TextureViewData view_data;
  bool convert_normal_map;
  T_FLOAT normal_scaling_factor;

  // Imgui用変数
  T_INT32 selected_size;
  T_INT32 selected_compression;
  T_INT32 selected_color_model;
  T_INT32 selected_filter;
  T_INT32 selected_address;
  T_INT32 selected_aniso_level;
  bool selected_fade_enabled;
  T_INT32 selected_fade_start;
  T_INT32 selected_fade_end;
  bool selected_convert_normal_map;
  T_FLOAT selected_normal_scaling_factor;
};

CEREAL_CLASS_VERSION(TextureAssetConverterSetting, 0);
