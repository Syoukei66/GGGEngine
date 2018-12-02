#include "DX11Shader.h"

#if GG_GRAPHICS_API_DX11

#include <d3dcompiler.h>
#include <Native/Windows/WindowsApplication.h>

HRESULT CompileShaderFromFile(const std::string& str, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
  HRESULT hr = S_OK;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows 
  // the shaders to be optimized and to run exactly the way they will run in 
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  ID3DBlob* pErrorBlob;
  hr = D3DCompile(
    str.c_str(), str.size(),
    NULL,
    NULL,
    NULL,
    szEntryPoint,
    szShaderModel,
    dwShaderFlags, 0,
    ppBlobOut,
    &pErrorBlob
  );
  if (FAILED(hr))
  {
    if (pErrorBlob != NULL)
      OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
    if (pErrorBlob) pErrorBlob->Release();
    return hr;
  }
  if (pErrorBlob) pErrorBlob->Release();

  return S_OK;
}


// =================================================================
// Constructor / Destructor
// =================================================================
DX11Shader::DX11Shader(const char* path)
{
  std::string code = FileUtil::TextFile_Read(path);

  // マクロ定義(#define)を読み込む
  D3D10_SHADER_MACRO macro;

  // インクルード(#include)を読み込む
  //ID3D10Include* 

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows 
  // the shaders to be optimized and to run exactly the way they will run in 
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();

  HRESULT hr = CompileShaderFromFile(code, "vert", "vs_4_0", &this->vs_brob_);
  GG_ASSERT(SUCCEEDED(hr), "頂点シェーダーのコンパイルに失敗しました");
  hr = device->CreateVertexShader(
    this->vs_brob_->GetBufferPointer(),
    this->vs_brob_->GetBufferSize(),
    NULL,
    &this->vertex_shader_
  );
  if (FAILED(hr))
  {
    this->vs_brob_->Release();
    GG_ASSERT(SUCCEEDED(hr), "頂点シェーダーのコンパイルに失敗しました");
  }

}

DX11Shader::~DX11Shader()
{
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
T_UINT8 DX11Shader::Begin()
{
  return T_UINT8();
}

void DX11Shader::BeginPass(T_UINT8 path_id)
{
}

void DX11Shader::CommitChanges()
{
}

void DX11Shader::EndPass()
{
}

void DX11Shader::End()
{
}

void DX11Shader::SetTechnique(const std::string& technique)
{
}

void DX11Shader::SetBool(const std::string& property_name, bool val)
{
}

void DX11Shader::SetInt(const std::string& property_name, T_INT32 val)
{
}

void DX11Shader::SetFloat(const std::string& property_name, T_FLOAT val)
{
}

void DX11Shader::SetVec2f(const std::string& property_name, const TVec2f& vec)
{
}

void DX11Shader::SetVec3f(const std::string& property_name, const TVec3f& vec)
{
}

void DX11Shader::SetVec4f(const std::string& property_name, const TVec4f& vec)
{
}

void DX11Shader::SetColor(const std::string& property_name, const TColor& color)
{
}

void DX11Shader::SetMatrix(const std::string& property_name, const Matrix4x4& matrix)
{
}

void DX11Shader::SetTexture(const std::string& property_name, const SharedRef<const rcTexture>& texture)
{
}

void DX11Shader::GetBool(const std::string& property_name, bool* dest)
{
}

void DX11Shader::GetInt(const std::string& property_name, T_INT32* dest)
{
}

void DX11Shader::GetFloat(const std::string& property_name, T_FLOAT* dest)
{
}

void DX11Shader::GetVec2f(const std::string& property_name, TVec2f* dest)
{
}

void DX11Shader::GetVec3f(const std::string& property_name, TVec3f* dest)
{
}

void DX11Shader::GetVec4f(const std::string& property_name, TVec4f* dest)
{
}

void DX11Shader::GetColor(const std::string& property_name, TColor* dest)
{
}

void DX11Shader::GetMatrix(const std::string& property_name, Matrix4x4* dest)
{
}

void DX11Shader::GetTexture(const std::string& property_name, void* native_dest)
{
}

D3DXHANDLE DX11Shader::GetHandle(const std::string& property_name)
{
  return D3DXHANDLE();
}

#endif
