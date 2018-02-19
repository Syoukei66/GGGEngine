#include "NativeShader.h"
#include "Director.h"

//inline static LPDIRECT3DVERTEXSHADER9 CompileVertexShader(const char* path)
//{
//  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
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
//  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
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
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
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
  this->effect_->SetTechnique(NULL);
  UINT path_count;
  this->effect_->Begin(&path_count, 0);
  return path_count;
}

void NativeShader::BeginPass(T_UINT8 path_id)
{
  HRESULT hr = this->effect_->BeginPass(path_id);
  NATIVE_ASSERT(SUCCEEDED(hr), "シェーダーパスの実行に失敗しました");
}

void NativeShader::CommitChanges()
{
  this->effect_->CommitChanges();
}

void NativeShader::EndPass()
{
  this->effect_->EndPass();
}

void NativeShader::End()
{
  this->effect_->End();
}

void NativeShader::SetBool(const char* property_name, bool val)
{
  this->effect_->SetBool(property_name, val);
}

void NativeShader::SetInt(const char* property_name, T_INT32 val)
{
  this->effect_->SetInt(property_name, val);
}

void NativeShader::SetFloat(const char* property_name, T_FLOAT val)
{
  this->effect_->SetFloat(property_name, val);
}

void NativeShader::SetVec2f(const char* property_name, const TVec2f& vec)
{
  this->effect_->SetFloatArray(property_name, (const T_FLOAT*)&vec, 2);
}

void NativeShader::SetVec3f(const char* property_name, const TVec3f& vec)
{
  this->effect_->SetFloatArray(property_name, (const T_FLOAT*)&vec, 3);
}

void NativeShader::SetVec4f(const char* property_name, const TVec4f& vec)
{
  this->effect_->SetFloatArray(property_name, (const T_FLOAT*)&vec, 4);
}

void NativeShader::SetColor(const char* property_name, const Color4F& color)
{
  this->effect_->SetFloatArray(property_name, color.GetColors(), 4);
}

void NativeShader::SetMatrix(const char* property_name, const NativeMatrixInstance* matrix)
{
  HRESULT hr = this->effect_->SetMatrix(property_name, (const D3DXMATRIX*)matrix);
}

void NativeShader::SetTexture(const char* property_name, NativeTextureInstance* texture)
{
  HRESULT hr = this->effect_->SetTexture(property_name, (LPDIRECT3DTEXTURE9)texture);
}

void NativeShader::GetBool(const char* property_name, bool* dest)
{
  BOOL ret;
  this->effect_->GetBool(property_name, &ret);
  *dest = ret;
}

void NativeShader::GetInt(const char* property_name, T_INT32* dest)
{
  this->effect_->GetInt(property_name, dest);
}

void NativeShader::GetFloat(const char* property_name, T_FLOAT* dest)
{
  this->effect_->GetFloat(property_name, dest);
}

void NativeShader::GetVec2f(const char* property_name, TVec2f* dest)
{
  this->effect_->GetFloatArray(property_name, (T_FLOAT*)dest, 2);
}

void NativeShader::GetVec3f(const char* property_name, TVec3f* dest)
{
  this->effect_->GetFloatArray(property_name, (T_FLOAT*)dest, 3);
}

void NativeShader::GetVec4f(const char* property_name, TVec4f* dest)
{
  this->effect_->GetFloatArray(property_name, (T_FLOAT*)dest, 4);
}

void NativeShader::GetColor(const char* property_name, Color4F* dest)
{
  this->effect_->GetFloatArray(property_name, (T_FLOAT*)dest, 4);
}

void NativeShader::GetMatrix(const char* property_name, INativeMatrix* dest)
{
  NATIVE_ASSERT(false, "まだできていません！");
  //this->effect_->GetMatrix(property_name, (D3DXMATRIX*)dest->GetNativeInstance());
}

void NativeShader::GetTexture(const char* property_name, INativeTexture* dest)
{
  NATIVE_ASSERT(false, "まだできていません！");
  //this->effect_->GetTexture(property_name, (LPDIRECT3DBASETEXTURE9*)(&(dest->GetNativeInstance())));
}
