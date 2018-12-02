#include "DX11Shader.h"

#if GG_GRAPHICS_API_DX11

#include <d3dcompiler.h>
#include <Native/Windows/WindowsApplication.h>
#include "DX11VertexDeclaration.h"

UniqueRef<rcShader> rcShader::CreateFromFile(const char* path)
{
  return UniqueRef<rcShader>(new DX11Shader(path));
}

HRESULT CompileShaderFromString(const std::string& str, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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

  // 頂点シェーダーコンパイル
  HRESULT hr = CompileShaderFromString(code, "vert", "vs_4_0", &this->vs_brob_);
  GG_ASSERT(SUCCEEDED(hr), "頂点シェーダーのコンパイルに失敗しました");
  hr = device->CreateVertexShader(
    this->vs_brob_->GetBufferPointer(),
    this->vs_brob_->GetBufferSize(),
    NULL,
    &this->vertex_shader_
  );
  GG_ASSERT(SUCCEEDED(hr), "頂点シェーダーの作成に失敗しました");

  // ピクセルシェーダーコンパイル
  hr = CompileShaderFromString(code, "frag", "ps_4_0", &this->ps_brob_);
  GG_ASSERT(SUCCEEDED(hr), "ピクセルシェーダーのコンパイルに失敗しました");
  hr = device->CreatePixelShader(
    this->ps_brob_->GetBufferPointer(),
    this->ps_brob_->GetBufferSize(),
    NULL,
    &this->pixel_shader_
  );
  GG_ASSERT(SUCCEEDED(hr), "ピクセルシェーダーの作成に失敗しました");

}

DX11Shader::~DX11Shader()
{
  this->vs_brob_->Release();
  this->vertex_shader_->Release();
  for (const auto& pair : this->input_layouts_)
  {
    pair.second->Release();
  }
  this->ps_brob_->Release();
  this->pixel_shader_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11Shader::SetInputLayout(const SharedRef<const rcVertexDeclaration>& declaration)
{
  ID3D11InputLayout* input_layout = nullptr;

  const auto& itr = this->input_layouts_.find(declaration->GetFormat());
  if (itr == this->input_layouts_.end())
  {
    const SharedRef<const DX11VertexDeclaration>& dx11_vertex_decl = SharedRef<const DX11VertexDeclaration>::StaticCast(declaration);

    ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();
    HRESULT hr = device->CreateInputLayout(
      dx11_vertex_decl->GetElements().data(), dx11_vertex_decl->GetElements().size(),
      this->vs_brob_->GetBufferPointer(), this->vs_brob_->GetBufferSize(),
      &input_layout
    );
    GG_ASSERT(SUCCEEDED(hr), "InputLayoutの作成に失敗しました");

    this->input_layouts_[declaration->GetFormat()] = input_layout;
  }
  else
  {
    input_layout = itr->second;
  }

  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->IASetInputLayout(input_layout);
}

T_UINT8 DX11Shader::Begin()
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  //context->VSSetConstantBuffers();

  // パスの数を返す
  return 1;
}

void DX11Shader::BeginPass(T_UINT8 path_id)
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->VSSetShader(this->vertex_shader_, NULL, 0);
  context->PSSetShader(this->pixel_shader_, NULL, 0);
}

void DX11Shader::CommitChanges()
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  //context->VSSetConstantBuffers();

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

#endif
