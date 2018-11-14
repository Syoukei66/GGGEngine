#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcIndexBuffer;

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
  static UniqueRef<rcVertexBuffer> Create(T_UINT32 vertex_count, T_UINT32 format);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

  virtual void SetStreamSource() const = 0;

  virtual void DrawIndexedPrimitive(const SharedRef<const rcIndexBuffer>& index_buffer, Vertex::PrimitiveType primitive_type) const = 0;

};