#include "NativeShader.h"
#include "Director.h"

//inline static LPDIRECT3DVERTEXSHADER9 CompileVertexShader(const char* path)
//{
//  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::->GetDevice();
//  LPDIRECT3DVERTEXSHADER9 ret = nullptr;
//  LPD3DXCONSTANTTABLE constant_table = nullptr;
//  LPD3DXBUFFER code = nullptr;
//  HRESULT hr = D3DXCompileShaderFromFile(
//    path,
//    NULL,
//    NULL,
//    "vert",
//    "vs_2_0",
//    D3DXSHADER_SKIPVALIDATION,
//    &code,
//    NULL,
//    &constant_table
//  );
//  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーのロードに失敗しました");
//
//  hr = device->CreateVertexShader((DWORD*)code->GetBufferPointer(), &ret);
//  code->Release();
//
//  return ret;
//}
//
//inline static LPDIRECT3DPIXELSHADER9 CompilePixelShader(const char* path)
//{
//  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::->GetDevice();
//  LPDIRECT3DPIXELSHADER9 ret = nullptr;
//  LPD3DXCONSTANTTABLE constant_table = nullptr;
//  LPD3DXBUFFER code = nullptr;
//  HRESULT hr = D3DXCompileShaderFromFile(
//    path,
//    NULL,
//    NULL,
//    "frag",
//    "ps_2_0",
//    D3DXSHADER_SKIPVALIDATION,
//    &code,
//    NULL,
//    &constant_table
//  );
//  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーのロードに失敗しました");
//
//  hr = device->CreatePixelShader((DWORD*)code->GetBufferPointer(), &ret);
//  code->Release();
//
//  return ret;
//}

static NativeShaderInstance* ShaderLoad(const char* path)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
  LPD3DXEFFECT dest = nullptr;

  HRESULT hr = D3DXCreateEffectFromFile(
    device,
    path,
    NULL,
    NULL,
    D3DXSHADER_SKIPVALIDATION,
    NULL,
    &dest,
    NULL
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーのロードに失敗しました");
  return (NativeShaderInstance*)dest;
}

// =================================================================
// Constructor / Destructor
// =================================================================
NativeShader::NativeShader(const char* path)
  : INativeShader(ShaderLoad(path))
{
  this->effect_ = this->GetNativeInstance<ID3DXEffect>();
}

NativeShader::~NativeShader()
{
  this->effect_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
T_UINT8 NativeShader::Begin()
{
  UINT path_count;
  HRESULT hr = this->effect_->Begin(&path_count, 0);
  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーの開始に失敗しました");
  return path_count;
}

void NativeShader::BeginPass(T_UINT8 path_id)
{
  HRESULT hr = this->effect_->BeginPass(path_id);
  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーパスの実行に失敗しました");
}

void NativeShader::CommitChanges()
{
  HRESULT hr = this->effect_->CommitChanges();
  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダープロパティの転送に失敗しました");
}

void NativeShader::EndPass()
{
  HRESULT hr = this->effect_->EndPass();
  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーパスの終了に失敗しました");
}

void NativeShader::End()
{
  HRESULT hr = this->effect_->End();
  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーの開始に失敗しました");
}

void NativeShader::SetTechnique(const std::string& technique)
{
  HRESULT hr = this->effect_->SetTechnique(technique.c_str());
  NATIVE_ASSERT(SUCCEEDED(hr), "テクニックの設定に失敗しました");
}

void NativeShader::SetBool(const std::string& property_name, bool val)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetBool(handle, val);
  NATIVE_ASSERT(SUCCEEDED(hr), "boolプロパティの転送に失敗しました");
}

void NativeShader::SetInt(const std::string& property_name, T_INT32 val)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetInt(handle, val);
  NATIVE_ASSERT(SUCCEEDED(hr), "intプロパティの転送に失敗しました");
}

void NativeShader::SetFloat(const std::string& property_name, T_FLOAT val)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloat(handle, val);
  NATIVE_ASSERT(SUCCEEDED(hr), "floatプロパティの転送に失敗しました");
}

void NativeShader::SetVec2f(const std::string& property_name, const TVec2f& vec)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloatArray(handle, vec.data, 2);
  NATIVE_ASSERT(SUCCEEDED(hr), "TVec2fプロパティの転送に失敗しました");
}

void NativeShader::SetVec3f(const std::string& property_name, const TVec3f& vec)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloatArray(handle, vec.data, 3);
  NATIVE_ASSERT(SUCCEEDED(hr), "TVec3fプロパティの転送に失敗しました");
}

void NativeShader::SetVec4f(const std::string& property_name, const TVec4f& vec)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloatArray(handle, vec.data, 4);
  NATIVE_ASSERT(SUCCEEDED(hr), "TVec4fプロパティの転送に失敗しました");
}

void NativeShader::SetColor(const std::string& property_name, const TColor& color)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetFloatArray(handle, color.data, 4);
  NATIVE_ASSERT(SUCCEEDED(hr), "TColorプロパティの転送に失敗しました");
}

void NativeShader::SetMatrix(const std::string& property_name, const Matrix4x4& matrix)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetMatrix(handle, (const D3DXMATRIX*)&matrix);
  NATIVE_ASSERT(SUCCEEDED(hr), "Matrix4x4プロパティの転送に失敗しました");
}

void NativeShader::SetTexture(const std::string& property_name, const Texture* texture)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  HRESULT hr = this->effect_->SetTexture(handle, texture ? (LPDIRECT3DTEXTURE9)texture->GetNativeObject() : nullptr);
  NATIVE_ASSERT(SUCCEEDED(hr), "Textureプロパティの転送に失敗しました");
}

void NativeShader::GetBool(const std::string& property_name, bool* dest)
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

void NativeShader::GetInt(const std::string& property_name, T_INT32* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetInt(handle, dest);
}

void NativeShader::GetFloat(const std::string& property_name, T_FLOAT* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloat(handle, dest);
}

void NativeShader::GetVec2f(const std::string& property_name, TVec2f* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloatArray(handle, dest->data, 2);
}

void NativeShader::GetVec3f(const std::string& property_name, TVec3f* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloatArray(handle, dest->data, 3);
}

void NativeShader::GetVec4f(const std::string& property_name, TVec4f* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloatArray(handle, dest->data, 4);
}

void NativeShader::GetColor(const std::string& property_name, TColor* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetFloatArray(handle, dest->data, 4);
}

void NativeShader::GetMatrix(const std::string& property_name, Matrix4x4* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  this->effect_->GetMatrix(handle, (D3DXMATRIX*)dest);
}

void NativeShader::GetTexture(const std::string& property_name, void* dest)
{
  D3DXHANDLE handle = GetHandle(property_name);
  if (!handle)
  {
    return;
  }
  NATIVE_ASSERT(false, "まだできていません！");
  this->effect_->GetTexture(handle, (LPDIRECT3DBASETEXTURE9*)(&(dest)));
}

D3DXHANDLE NativeShader::GetHandle(const std::string& property_name)
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
