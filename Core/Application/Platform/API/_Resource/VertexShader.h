#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcVertexDeclaration;

/*!
 * @brief �s�N�Z���V�F�[�_�[�̊��N���X
 * �v���b�g�t�H�[�����̏�����h���N���X���Œ�`����
 */
class rcVertexShader : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcVertexShader);
  GG_NATIVE_CREATE_FUNC_1(rcVertexShader, const std::vector<unsigned char>&, byte_code);
  
  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetInputLayout(const SharedRef<const rcVertexDeclaration>& declaration) const = 0;
  virtual void SetShader() const = 0;

};