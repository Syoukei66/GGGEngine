#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcIndexBuffer;
class rcVertexDeclaration;
class rcShader;

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

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcVertexBuffer> Create(T_UINT32 size);
  static UniqueRef<rcVertexBuffer> Create(T_UINT32 size, void* data);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

  virtual void SetStreamSource(const SharedRef<const rcVertexDeclaration>& declaration) const = 0;

};