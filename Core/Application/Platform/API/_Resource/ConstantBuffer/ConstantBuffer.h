#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>
#include <Core/Constants/ShaderUtils.h>

/*!
 * @brief �萔�o�b�t�@�N���X
 * �v���b�g�t�H�[�����̏�����h���N���X���Œ�`����
 */
class rcConstantBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcConstantBuffer);

protected:
  rcConstantBuffer(Shader::ConstantBufferId id)
    : id_(id)
  {
  }

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcConstantBuffer> Create(Shader::ConstantBufferId id, T_UINT32 size);
  static UniqueRef<rcConstantBuffer> Create(Shader::ConstantBufferId id, T_UINT32 size, const void* data);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void CommitChanges(const void* data) = 0;
  virtual void SetBuffer() const = 0;

  // =================================================================
  // Data Members
  // =================================================================
protected:
  Shader::ConstantBufferId id_;

};
