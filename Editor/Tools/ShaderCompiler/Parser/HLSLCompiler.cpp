#include "HLSLCompiler.h"

#include "ShaderToken.h"

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

class GGInclude : public ID3DInclude
{
public:
  GGInclude() { aPath.push_back(""); }

  HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
  {
    switch (IncludeType) {
      // ‚Æ‚è‚ ‚¦‚¸""‚Æ<>‚Ì‹æ•Ê‚È‚µ
    case D3D_INCLUDE_LOCAL:
    case D3D_INCLUDE_SYSTEM:
      break;
    default:
      return E_FAIL;
    }

    for (auto& p : aPath) {
      std::string path = p;
      path += pFileName;

      std::ifstream input;
      input.open(path.c_str(), std::ios::binary);
      if (!input.is_open())continue;

      size_t fsize = (size_t)input.seekg(0, std::ios::end).tellg();
      input.seekg(0, std::ios::beg);

      void* data = ::operator new(fsize);
      input.read(reinterpret_cast<char*>(data), fsize);
      *ppData = data;
      *pBytes = fsize;
      return S_OK;
    }
    return E_FAIL;
  }
  HRESULT __stdcall Close(LPCVOID pData)
  {
    ::operator delete(const_cast<void*>(pData));
    return S_OK;
  }

  std::vector<std::string> aPath;
};

void CompileShaderFromString(const std::string& str, const std::string& include_path, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows 
  // the shaders to be optimized and to run exactly the way they will run in 
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  ID3DBlob* pErrorBlob;
  GGInclude inc = GGInclude();
  inc.aPath.push_back(include_path);
  HRESULT hr = D3DCompile(
    str.c_str(), str.size(),
    NULL,
    NULL,
    &inc,
    szEntryPoint,
    szShaderModel,
    dwShaderFlags, 0,
    ppBlobOut,
    &pErrorBlob
  );
  if (FAILED(hr))
  {
    if (pErrorBlob)
    {
      HLSLCompileException e(szShaderModel, (char*)pErrorBlob->GetBufferPointer());
      pErrorBlob->Release();
      throw e;
    }
  }
}

HLSLCompiler::HLSLCompiler(const std::string& input_directory_path)
  : input_directory_path_(input_directory_path)
{
}

void HLSLCompiler::ConvertHLSL(const ShaderData& shader, std::string* str)
{
  std::string builtin = "";
  builtin += "cbuffer RendererBuiltin : register( b0 )\n";
  builtin += "{\n";
  builtin += "  matrix _MatMVP;\n";
  builtin += "  matrix _MatMV;\n";
  builtin += "  matrix _ObjToWorld;\n";
  builtin += "  matrix _WorldToObj;\n";
  builtin += "  float4 _Time;\n";
  builtin += "  float4 _SinTime;\n";
  builtin += "  float4 _CosTime;\n";
  builtin += "};\n";
  builtin += "cbuffer GameObjectRenderStateBuiltin : register( b1 )\n";
  builtin += "{\n";
  builtin += "  matrix _MatV;\n";
  builtin += "  matrix _MatP;\n";
  builtin += "  float4 _CameraPosition;\n";
  builtin += "  float4 _CameraDirection;\n";
  builtin += "  float4 _DeltaTime;\n";
  builtin += "};\n";

  std::string user = "";
  user += "cbuffer UserProperty : register( b2 )\n";
  user += "{\n";
  for (const ScalaPropertyData& data : shader.scala_properties_)
  {
    user += "  " + GGGShaderParser::VariableTypeTokens[data.variable_type_] + " " + data.name_ + " = " 
      + std::to_string(data.init_value_) + ";\n";
  }
  for (const VectorPropertyData& data : shader.vector_properties_)
  {
    user += "  " + GGGShaderParser::VariableTypeTokens[data.variable_type_] + "4 " + data.name_ + " = { "
      + std::to_string(data.init_value0_) + ", "
      + std::to_string(data.init_value1_) + ", "
      + std::to_string(data.init_value2_) + ", "
      + std::to_string(data.init_value3_) + " };\n";
  }
  for (const ColorPropertyData& data : shader.color_properties_)
  {
    user += "  " + GGGShaderParser::VariableTypeTokens[static_cast<T_FIXED_UINT8>(Shader::VariableType::kFloat)] + "4 " + data.name_ + " = { "
      + std::to_string(data.init_r_) + ", "
      + std::to_string(data.init_g_) + ", "
      + std::to_string(data.init_b_) + ", "
      + std::to_string(data.init_a_) + " };\n";
  }
  user += "};\n";
  T_UINT32 texture_index = 0;
  for (const SamplerPropertyData& data : shader.sampler_properties_)
  {
    const std::string tex_name = data.name_;
    const std::string sampler_name = data.name_ + "Sampler";
    user += "Texture2D " + tex_name + " : register( t" + std::to_string(texture_index) + " );\n";
    user += "SamplerState " + sampler_name + " : register( s" + std::to_string(texture_index) + " );\n";
    ++texture_index;

    const std::string target = "tex2D(" + tex_name;
    const std::string replace = tex_name + ".Sample(" + sampler_name;
    auto pos = str->find(target);
    auto len = target.length();
    if (pos != std::string::npos) 
    {
      str->replace(pos, len, replace);
    }
  }

  (*str) = builtin + user + (*str);

  Log::Info(str->c_str());
}

void HLSLCompiler::CompileVertexShader(const std::string& str, std::vector<unsigned char>* dest)
{
  ID3DBlob* vs_blob;
  CompileShaderFromString(str, this->input_directory_path_, "VS", "vs_4_0", &vs_blob);

  const T_UINT32 vs_size = (T_UINT32)vs_blob->GetBufferSize();
  dest->resize(vs_size);
  for (T_UINT32 i = 0; i < vs_size; ++i)
  {
    (*dest)[i] = ((unsigned char*)vs_blob->GetBufferPointer())[i];
  }
}

void HLSLCompiler::CompilePixelShader(const std::string& str, std::vector<unsigned char>* dest)
{
  ID3DBlob* ps_blob;
  CompileShaderFromString(str, this->input_directory_path_, "PS", "ps_4_0", &ps_blob);

  const T_UINT32 ps_size = (T_UINT32)ps_blob->GetBufferSize();
  dest->resize(ps_size);
  for (T_UINT32 i = 0; i < ps_size; ++i)
  {
    (*dest)[i] = ((unsigned char*)ps_blob->GetBufferPointer())[i];
  }
}
