#pragma once

#include "Texture.h"

class rcDynamicTexture : public rcTexture
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcDynamicTexture);
  GG_ASSET(rcDynamicTexture, TextureData);
  GG_CREATE_FUNC(rcDynamicTexture) { return rcTexture::Init(); }
  GG_DESTRUCT_FUNC(rcDynamicTexture);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief �s�N�Z���}�b�v���쐬����
   */
  void CreatePixels(T_FIXED_UINT16 width, T_FIXED_UINT16 height, Shader::TextureFormat format);

  /*!
   * @brief �s�N�Z���}�b�v�̕ύX���m�肷��
   */
  void CommitPixels(rcTextureResource::Usage usage = rcTextureResource::Usage::kUltraDynamic);

  /*!
   * @brief �s�N�Z���}�b�v���폜����
   */
  void ClearPixels();

  /*!
   * @brief DynamicTexture�𕡐�����
   */
  GG_INLINE SharedRef<rcDynamicTexture> Clone() const
  {
    return rcDynamicTexture::Create(this->data_);
  }

  /*!
   * @brief �ҏW�s�̃N���[�����쐬����
   */
  GG_INLINE SharedRef<rcTexture> CloneStatic() const
  {
    return rcTexture::Create(this->data_);
  }

  /*!
   * @brief �ҏW�s�̃N���[���Ƀf�[�^���ړ�����B
   * CloneStatic������R�X�g�������̃��\�b�h���g�p��A
   * ����DynamicTexture�͎g�p�s�ɂȂ�B
   * immutable��commit�������̂ł����CommitPixels��肱������g�p������������
   */
  SharedRef<rcTexture> MoveStatic();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  /*!
   * @brief �s�N�Z���̏����擾����B
   * �f�[�^�`���̓s�N�Z���t�H�[�}�b�g�ɂ���ĈقȂ�
   * @param x �e�N�Z��X���W
   * @param y �e�N�Z��Y���W
   * @return �w�肳�ꂽ���W�̃s�N�Z���f�[�^�̐擪�|�C���^
   */
  GG_INLINE unsigned char* GetPixel(const T_UINT16 x, T_UINT16 y)
  {
    return &this->data_.resource_data_.data_[(this->width_ * y + x) * this->bytes_per_pixel_];
  }

  /*!
   * @brief �s�N�Z���̏����擾����B
   * �f�[�^�`���̓s�N�Z���t�H�[�}�b�g�ɂ���ĈقȂ�
   * @param x �e�N�Z��X���W
   * @param y �e�N�Z��Y���W
   * @return �w�肳�ꂽ���W�̃s�N�Z���f�[�^�̐擪�|�C���^
   */
  GG_INLINE const unsigned char* GetPixel(const T_UINT16 x, T_UINT16 y) const
  {
    return &this->data_.resource_data_.data_[(this->width_ * y + x) * this->bytes_per_pixel_];
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  TextureData data_;
  T_UINT8 bytes_per_pixel_;
  bool is_new_resource_;

};
