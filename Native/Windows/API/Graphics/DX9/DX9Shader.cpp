#include "DX9Shader.h"

#if GG_GRAPHICS_API_DX9

#include <Native/Windows/WindowsApplication.h>
#include "DX9VertexDeclaration.h"

UniqueRef<rcShader> rcShader::CreateFromFile(const char* path)
{
  return UniqueRef<rcShader>(new DX9Shader(path));
}

// =================================================================
// Constructor / Destructor
// =================================================================
DX9Shader::DX9Shader(const char* path)
{
  LPD3DXBUFFER error_buffer = nullptr;
  IDirect3DDevice9* device = WindowsPlatform::GetDX9Graphics()->GetDevice();

  HRESULT hr = D3DXCreateEffectFromFile(
    device,
    path,
    NULL,
    NULL,
    D3DXSHADER_SKIPVALIDATION,
    NULL,
    &this->effect_,
    &error_buffer
  );
  if (FAILED(hr))
  {
    Log::Error(("シェーダーのロードに失敗しました" + (error_buffer ? "\n=>" + std::string((LPCSTR)error_buffer->GetBufferPointer()) : "")).c_str());
  }
}

DX9Shader::~DX9Shader()
{
  this->effect_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX9Shader::SetInputLayout(const SharedRef<const rcVertexDeclaration>& declaration)
{
  SharedRef<const DX9VertexDeclaration>::StaticCast(declaration)->SetDeclaration();
}

T_UINT8 DX9Shader::Begin()
{
  UINT path_count;
  HRESULT hr = this->effect_->Begin(&path_count, 0);
  GG_ASSERT(SUCCEEDED(hr), "シェーダーの開始に失敗しました");
  return path_count;
}

void DX9Shader::BeginPass(T_UINT8 path_id)
{
  HRESULT hr = this->effect_->BeginPass(path_id);
  GG_ASSERT(SUCCEEDED(hr), "シェーダーパスの実行に失敗しました");
}

void DX9Shader::CommitChanges()
{
  HRESULT hr = this->effect_->CommitChanges();
  GG_ASSERT(SUCCEEDED(hr), "シェーダープロパティの転送に失敗しました");
}

void DX9Shader::EndPass()
{
  HRESULT hr = this->effect_->EndPass();
  GG_ASSERT(SUCCEEDED(hr), "シェーダーパスの終了に失敗しました");
}

void DX9Shader::End()
{
  HRESULT hr = this->effect_->End();
  GG_ASSERT(SUCCEEDED(hr), "シェーダーの開始に失敗しました");
}

void DX9Shader::SetTechnique(const std::string& technique)
{
  HRESULT hr = this->effect_->SetTechnique(technique.c_str());
  GG_ASSERT(SUCCEEDED(hr), "テクニックの設定に失敗しました");
}

void DX9Shader::SetBool(const std::string& property_name, bool val)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetBool(handle, val);
  GG_ASSERT(SUCCEEDED(hr), "boolプロパティの転送に失敗しました");
}

void DX9Shader::SetInt(const std::string& property_name, T_INT32 val)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetInt(handle, val);
  GG_ASSERT(SUCCEEDED(hr), "intプロパティの転送に失敗しました");
}

void DX9Shader::SetFloat(const std::string& property_name, T_FLOAT val)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloat(handle, val);
  GG_ASSERT(SUCCEEDED(hr), "floatプロパティの転送に失敗しました");
}

void DX9Shader::SetVec2f(const std::string& property_name, const TVec2f& vec)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloatArray(handle, vec.data, 2);
  GG_ASSERT(SUCCEEDED(hr), "TVec2fプロパティの転送に失敗しました");
}

void DX9Shader::SetVec3f(const std::string& property_name, const TVec3f& vec)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloatArray(handle, vec.data, 3);
  GG_ASSERT(SUCCEEDED(hr), "TVec3fプロパティの転送に失敗しました");
}

void DX9Shader::SetVec4f(const std::string& property_name, const TVec4f& vec)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloatArray(handle, vec.data, 4);
  GG_ASSERT(SUCCEEDED(hr), "TVec4fプロパティの転送に失敗しました");
}

void DX9Shader::SetColor(const std::string& property_name, const TColor& color)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloatArray(handle, color.data, 4);
  GG_ASSERT(SUCCEEDED(hr), "TColorプロパティの転送に失敗しました");
}

void DX9Shader::SetMatrix(const std::string& property_name, const Matrix4x4& matrix)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetMatrix(handle, (const D3DXMATRIX*)&matrix);
  GG_ASSERT(SUCCEEDED(hr), "Matrix4x4プロパティの転送に失敗しました");
}

void DX9Shader::SetTexture(const std::string& property_name, const SharedRef<const rcTexture>& texture)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetTexture(handle, texture ? (LPDIRECT3DTEXTURE9)texture->GetNativeObject() : nullptr);
  GG_ASSERT(SUCCEEDED(hr), "rcTextureプロパティの転送に失敗しました");
}

void DX9Shader::GetBool(const std::string& property_name, bool* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  BOOL ret;
  this->effect_->GetBool(handle, &ret);
  *dest = ret;
}

void DX9Shader::GetInt(const std::string& property_name, T_INT32* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetInt(handle, dest);
}

void DX9Shader::GetFloat(const std::string& property_name, T_FLOAT* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloat(handle, dest);
}

void DX9Shader::GetVec2f(const std::string& property_name, TVec2f* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloatArray(handle, dest->data, 2);
}

void DX9Shader::GetVec3f(const std::string& property_name, TVec3f* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloatArray(handle, dest->data, 3);
}

void DX9Shader::GetVec4f(const std::string& property_name, TVec4f* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloatArray(handle, dest->data, 4);
}

void DX9Shader::GetColor(const std::string& property_name, TColor* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloatArray(handle, dest->data, 4);
}

void DX9Shader::GetMatrix(const std::string& property_name, Matrix4x4* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetMatrix(handle, (D3DXMATRIX*)dest);
}

void DX9Shader::GetTexture(const std::string& property_name, void* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  GG_ASSERT(false, "まだできていません！");
  this->effect_->GetTexture(handle, (LPDIRECT3DBASETEXTURE9*)(&(dest)));
}

D3DXHANDLE DX9Shader::GetHandle(const std::string& property_name)
{
  if (this->bad_property_ids_.find(property_name) != this->bad_property_ids_.end())
  {
    return NULL;
  }
  auto pair = this->property_handles_.find(property_name);
  //プロパティが登録されていたらハンドルを返す
  if (pair != this->property_handles_.end())
  {
    return pair->second;
  }
  D3DXHANDLE ret = this->effect_->GetParameterByName(NULL, property_name.c_str());
  if (ret)
  {
    this->property_handles_.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(property_name),
      std::forward_as_tuple(ret));
    return ret;
  }
  this->bad_property_ids_.insert(property_name);
  return NULL;
}

#endif