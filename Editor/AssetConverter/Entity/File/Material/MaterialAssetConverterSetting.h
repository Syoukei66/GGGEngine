#pragma once

#include <Entity/ConverterSetting.h>

/*!
 * @brief MaterialAssetConverterの設定
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
   * @brief デフォルトコンストラクタ。シリアライズ用
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
   * @brief シェーダーからプロパティを取得する
   */
  void StoreShaderProperties(const MaterialData& data);

  // =================================================================
  // Data Members
  // =================================================================
public:
  /*!
   * @brief 最新のデータを持っているか
   */
  bool is_master_;

  /*!
   * @brief データが更新されたか
   */
  bool is_updated_;
  MaterialData edit_data_;
};

CEREAL_CLASS_VERSION(MaterialAssetConverterSetting, 0);
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(MaterialAssetConverterSetting, cereal::specialization::member_load_save)