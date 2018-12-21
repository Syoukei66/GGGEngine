#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief テクスチャサンプラのデータ
 */
struct TextureSamplerData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TextureSamplerData)
  {
    archive(filter_);
    archive(address_u_);
    archive(address_v_);
    archive(aniso_level_);
    archive(fade_start_);
    archive(fade_end_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureSamplerData()
    : filter_(static_cast<T_FIXED_UINT8>(Shader::TextureFilter::kBilinear))
    , address_u_(static_cast<T_FIXED_UINT8>(Shader::TextureAddress::kClamp))
    , address_v_(static_cast<T_FIXED_UINT8>(Shader::TextureAddress::kClamp))
    , aniso_level_(1)
    , fade_start_(0)
    , fade_end_(0)
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT8 filter_; // TextureFilter
  T_FIXED_UINT8 address_u_; // TextureAddress
  T_FIXED_UINT8 address_v_; // TextureAddress
  T_FIXED_UINT8 aniso_level_;

  // start == end == 0で無効(デフォルト)
  T_FIXED_UINT8 fade_start_;
  T_FIXED_UINT8 fade_end_;
};

/*!
 * @brief テクスチャサンプラの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcTextureSampler : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTextureSampler);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcTextureSampler> Create(const TextureSamplerData& data);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetSampler(T_UINT8 index) const = 0;

};