#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief �s�N�Z���V�F�[�_�[�̊��N���X
 * �v���b�g�t�H�[�����̏�����h���N���X���Œ�`����
 */
class rcPixelShader : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcPixelShader);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcPixelShader> Create(const std::vector<unsigned char>& byte_code);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetShader() const = 0;

};