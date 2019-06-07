#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>
#include <Core/Application/Platform/API/_Resource/TextureResource.h>

/*!
 * @brief テクスチャビューのデータ
 */
struct TextureViewData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TextureViewData)
  {
    archive(filter_);
    archive(address_u_);
    archive(address_v_);
    archive(aniso_level_);
    archive(mip_map_levels_);
    archive(fade_enabled_);
    archive(fade_start_);
    archive(fade_end_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureViewData()
    : filter_(static_cast<T_FIXED_UINT8>(Shader::TextureFilter::kTrilinear))
    , address_u_(static_cast<T_FIXED_UINT8>(Shader::TextureAddress::kWrap))
    , address_v_(static_cast<T_FIXED_UINT8>(Shader::TextureAddress::kWrap))
    , aniso_level_(1)
    , mip_map_levels_(1)
    , fade_enabled_()
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
  T_FIXED_UINT8 mip_map_levels_;

  bool fade_enabled_;
  T_FIXED_UINT8 fade_start_; // 0-10
  T_FIXED_UINT8 fade_end_; // 0-10
};

/*!
 * @brief テクスチャビューの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcTextureView : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTextureView);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcTextureView> Create(const TextureViewData& data, const SharedRef<rcTextureResource>& resource);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetToHardware(T_UINT8 index) const = 0;
  virtual ImTextureID GetImTextureID() const = 0;

};