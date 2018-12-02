#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief ���_���̃x�[�X�N���X
 * �v���b�g�t�H�[�����̏�����h���N���X���Œ�`����B
 */
class rcVertexDeclaration : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcVertexDeclaration);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcVertexDeclaration> Create(T_UINT32 format);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual T_UINT32 GetFormat() const = 0;
  virtual T_UINT32 GetVertexSize() const = 0;

};
