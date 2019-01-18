#pragma once

#include <Entity/File/FileAssetConverter.h>
#include <Cereal/cereal.hpp>

/*!
 * @brief TextureAssetConverterÇÃê›íË
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
  TextureAssetConverterSetting(const std::string& converter_id)
    : ConverterSetting(converter_id)
    , max_size(2048)
    , compression(static_cast<T_FIXED_UINT8>(CompressionQuality::kNormal))
    , color_model(static_cast<T_FIXED_UINT8>(ColorModel::kRGBA))
    , view_data()
  {}

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

class TextureAssetConverter : public FileAssetConverter<rcTexture, TextureData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureAssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<std::string>& extensions,
    T_UINT32 skip_head, T_UINT32 skip_tail
  )
    : FileAssetConverter(id, class_name, extensions, skip_head, skip_tail)
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual IAssetDataContainer* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const override;

  virtual std::unique_ptr<ConverterSetting> CreateSetting() const
  {
    return std::unique_ptr<ConverterSetting>(new TextureAssetConverterSetting(this->GetId()));
  }

};
