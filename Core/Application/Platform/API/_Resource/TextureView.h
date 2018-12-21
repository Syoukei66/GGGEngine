#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>
#include <Core/Application/Platform/API/_Resource/TextureResource.h>

/*!
 * @brief �e�N�X�`���r���[�̃f�[�^
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
    archive(fade_start_);
    archive(fade_end_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureViewData()
    : filter_(static_cast<T_FIXED_UINT8>(Shader::TextureFilter::kBilinear))
    , address_u_(static_cast<T_FIXED_UINT8>(Shader::TextureAddress::kWrap))
    , address_v_(static_cast<T_FIXED_UINT8>(Shader::TextureAddress::kWrap))
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

  // start == end == 0�Ŗ���(�f�t�H���g)
  T_FIXED_UINT8 fade_start_;
  T_FIXED_UINT8 fade_end_;
};

/*!
 * @brief �e�N�X�`���r���[�̊��N���X
 * �v���b�g�t�H�[�����̏�����h���N���X���Œ�`����
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

};