#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>
#include <Core/Constants/ShaderUtils.h>

/*!
 * @brief 定数バッファクラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcConstantBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcConstantBuffer);
  GG_INIT_FUNC_1(rcConstantBuffer, Shader::ConstantBufferId, id)
  {
    this->id_ = id;
    return true;
  }
  GG_NATIVE_CREATE_FUNC_2(rcConstantBuffer, Shader::ConstantBufferId, id, T_UINT32, size);
  GG_NATIVE_CREATE_FUNC_3(rcConstantBuffer, Shader::ConstantBufferId, id, T_UINT32, size, const void*, data);

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
