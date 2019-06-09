#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcVertexDeclaration;

/*!
 * @brief ���_�o�b�t�@�̃x�[�X�N���X�B
 * �v���b�g�t�H�[�����̏�����h���N���X���Œ�`����B
 */
class rcVertexBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcVertexBuffer);
  GG_NATIVE_CREATE_FUNC_1(rcVertexBuffer, T_UINT32, size);
  GG_NATIVE_CREATE_FUNC_2(rcVertexBuffer, T_UINT32, size, void*, data);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

  virtual void SetStreamSource(const SharedRef<const rcVertexDeclaration>& declaration) const = 0;

};