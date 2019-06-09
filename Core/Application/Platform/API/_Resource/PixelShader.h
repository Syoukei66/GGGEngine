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
  GG_NATIVE_CREATE_FUNC_1(rcPixelShader, const std::vector<unsigned char>&, byte_code);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetShader() const = 0;

};