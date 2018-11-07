#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief �C���f�b�N�X�o�b�t�@�̊��N���X
 * API���̏�����h���N���X���Œ�`����
 */
class rcIndexBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(rcIndexBuffer);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcIndexBuffer> Create(T_UINT32 vertex_count, T_UINT32 polygon_count);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;
  virtual void SetIndices() const = 0;
  
  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual T_UINT32 GetVertexesCount() const = 0;
  virtual T_UINT32 GetPolygonCount() const = 0;

};