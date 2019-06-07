#pragma once

#include <Core/Application/Platform/API/_Resource/TextureResource.h>
#include <Core/Application/Platform/API/_Resource/TextureView.h>

/*!
 * @brief �V�F�[�_�[���\�[�X�Ƃ��Ẵe�N�X�`���̃f�[�^
 */
struct TextureData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TextureData)
  {
    archive(resource_data_);
    archive(view_data_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureData()
    : resource_data_()
    , view_data_()
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  TextureResourceData resource_data_;
  TextureViewData view_data_;
};

/*!
 * @brief �V�F�[�_�[���\�[�X�Ƃ��Ă�2D�e�N�X�`��
 */
class rcTexture : public GGAssetObject
{
  friend class rcDynamicTexture;

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTexture);
  GG_ASSET(rcTexture, TextureData);
  GG_CREATE_FUNC(rcTexture) { return true; }

  // =================================================================
  // Method 
  // =================================================================
public:
  void SetToHardware(T_UINT8 index) const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<const rcTextureResource> GetTextureResource() const
  {
    return this->resource_;
  }
  GG_INLINE SharedRef<const rcTextureView> GetTextureView() const
  {
    return this->view_;
  }

  GG_INLINE T_UINT16 GetWidth() const
  {
    return this->width_;
  }
  GG_INLINE T_UINT16 GetHeight() const
  {
    return this->height_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  SharedRef<rcTextureResource> resource_;
  SharedRef<rcTextureView> view_;

  // �e�N�X�`���̃e�N�Z���T�C�Y�A
  // DynamicTexture�̃T�C�Y�ȂǁA�Q�̗ݏ�ł͂Ȃ��ꍇ������B
  T_UINT16 width_;
  T_UINT16 height_;
};