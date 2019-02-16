#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief �e�N�X�`�����\�[�X�̃f�[�^
 */
struct TextureResourceData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(TextureResourceData)
  {
    archive(bits_per_pixel_);
    archive(block_size_);
    archive(mip_map_levels_);
    archive(width_);
    archive(height_);
    archive(format_);
    archive(data_);
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureResourceData()
    : bits_per_pixel_(1)
    , block_size_(1)
    , mip_map_levels_(1)
    , width_(1)
    , height_(1)
    , format_(static_cast<T_FIXED_UINT8>(Shader::TextureFormat::kR8G8B8A8_UINT))
    , data_()
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT8 bits_per_pixel_;
  T_FIXED_UINT8 block_size_;
  T_FIXED_UINT8 mip_map_levels_;
  T_FIXED_UINT16 width_; // two power value
  T_FIXED_UINT16 height_; // two power value
  T_FIXED_UINT8 format_; // TextureFormat
  std::vector<unsigned char> data_;
};

/*!
 * @brief �e�N�X�`�����\�[�X�̊��N���X
 * �v���b�g�t�H�[�����̏�����h���N���X���Œ�`����
 */
class rcTextureResource : public GGAPIResourceObject
{
public:
  // �e�N�X�`���̗p�r
  enum class Usage
  {
    // �ύX�s��&�Q�ƕs��
    kImmutable,

    // �ύX�s��&�Q�Ɖ\
    kReadable,

    // �ύX�\&�Q�ƕs��
    kDynamic,

    // �ύX�\&�Q�Ɖ\
    kDynamicReadable,
  };

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTextureResource);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcTextureResource> Create(const TextureResourceData& data, Usage usage = Usage::kImmutable);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

};