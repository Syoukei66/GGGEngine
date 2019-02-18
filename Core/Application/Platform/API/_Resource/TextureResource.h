#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief �e�f�[�^�쐬�ς݂̃e�N�X�`�����\�[�X�̃f�[�^
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
    : bits_per_pixel_(0)
    , block_size_(0)
    , mip_map_levels_(0)
    , width_(1)
    , height_(1)
    , format_(static_cast<T_FIXED_UINT8>(Shader::TextureFormat::kRGB))
    , data_()
  {}

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_FIXED_UINT8 bits_per_pixel_; // 0�̏ꍇ���s���Ɍv�Z�����
  T_FIXED_UINT8 block_size_;     // 0�̏ꍇ���s���Ɍv�Z�����
  T_FIXED_UINT8 mip_map_levels_; // 0�̏ꍇ���s���Ɍv�Z�����
  T_FIXED_UINT16 width_; // two power value
  T_FIXED_UINT16 height_; // two power value
  T_FIXED_UINT8 format_; // TextureFormat

  // bits_per_pixel_��1�ȏ�̏ꍇ�̓v���b�g�t�H�[�������ɍœK������Ă���ׁA
  // �o�C�g�z���p�����s�N�Z���ւ̃A�N�Z�X�͎g�p�ł��Ȃ��B�i����`�j
  // bits_per_pixel_��0�̏ꍇ�͔�œK���f�[�^�Ȃ̂�
  // ���̏ꍇ��format_��������Shader::GetBytePerPixel��p���鎖��
  // ���ۂ̃s�N�Z��������̃o�C�g�����擾�ł���B
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
    // �ύX���Ȃ�
    kImmutable,

    // �ύX����
    // TODO:Map/Unmap UpdateSubresource�̃R�X�g�Ɋւ��郊�T�[�`������
    // UpdateSubresource�ł̃��\�[�X�̍X�V�ɈӋ`�����������������
    //kDynamic,

    // �قږ��t���[���ύX����
    kUltraDynamic,
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
  virtual void UpdateSubresource(const TextureResourceData& data, Usage usage = Usage::kImmutable) = 0;

};