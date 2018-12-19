#include "ShaderAssetImporter.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ShaderAssetImporter::ShaderAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================

#include <d3dcompiler.h>

class GGInclude : public ID3DInclude
{
public:
  GGInclude() { aPath.push_back(""); }

  HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
  {
    switch (IncludeType) {
      // とりあえず""と<>の区別なし
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


HRESULT CompileShaderFromString(const std::string& str, const std::string& include_path, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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
  GGInclude inc = GGInclude();
  inc.aPath.push_back(include_path);
  hr = D3DCompile(
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
    if (pErrorBlob != NULL)
      OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
    if (pErrorBlob) pErrorBlob->Release();
    return hr;
  }
  if (pErrorBlob) pErrorBlob->Release();

  return S_OK;
}

SharedRef<ShaderAssetEntity> ShaderAssetImporter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context)
{
  ShaderData* data = new ShaderData();

  data->name_ = "test";

  PassData pass = PassData();

  std::string code = FileUtil::TextFile_Read(meta->GetInputPath().c_str());

  // 頂点シェーダーコンパイル
  ID3DBlob* vs_blob;
  HRESULT hr = CompileShaderFromString(code, meta->GetInputDirectoryPath(), "VS", "vs_4_0", &vs_blob);
  GG_ASSERT(SUCCEEDED(hr), "頂点シェーダーのコンパイルに失敗しました");

  // ピクセルシェーダーコンパイル
  ID3DBlob* ps_blob;
  hr = CompileShaderFromString(code, meta->GetInputDirectoryPath(), "PS", "ps_4_0", &ps_blob);
  GG_ASSERT(SUCCEEDED(hr), "ピクセルシェーダーのコンパイルに失敗しました");

  const T_UINT32 vs_size = (T_UINT32)vs_blob->GetBufferSize();
  pass.vs_byte_code_.resize(vs_size);
  for (T_UINT32 i = 0; i < vs_size; ++i)
  {
    pass.vs_byte_code_[i] = ((unsigned char*)vs_blob->GetBufferPointer())[i];
  }
  const T_UINT32 ps_size = (T_UINT32)ps_blob->GetBufferSize();
  pass.ps_byte_code_.resize(ps_size);
  for (T_UINT32 i = 0; i < ps_size; ++i)
  {
    pass.ps_byte_code_[i] = ((unsigned char*)ps_blob->GetBufferPointer())[i];
  }
  data->passes_.emplace_back(pass);

  return ShaderAssetEntity::Create(meta, data);
}
