#include "TextureAssetImporter.h"
#include <Entity/AssetMetaData.h>
#include <DirectXTex.h>
#include <Editor/ThirdParty/DirectXTex/WICTextureLoader/WICTextureLoader.h>

#pragma comment(lib, "DirectXTex.lib")

// =================================================================
// Constructor / Destructor
// =================================================================
TextureAssetImporter::TextureAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================
void* TextureAssetImporter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context)
{
  TextureData* data = new TextureData();

  ID3D11Resource* texture;
  ID3D11ShaderResourceView* shader_resource_view;

  WCHAR	wpath[256] = {};

  errno_t err = 0;

  //ロケール指定
  setlocale(LC_ALL, "japanese");
  //変換
  err = mbstowcs(wpath, meta->GetInputPath().c_str(), sizeof(wpath));
  DirectX::TexMetadata metadata;
  DirectX::ScratchImage image;

  HRESULT hr = S_FALSE;
  if (meta->GetURI().GetExtension() == "tga")
  {
    hr = DirectX::LoadFromTGAFile(wpath, &metadata, image);
  }
  else
  {
    hr = DirectX::LoadFromWICFile(wpath, 0, &metadata, image);
  }
  GG_ASSERT(SUCCEEDED(hr), "テクスチャの読み込みに失敗しました");

  data->resource_data_.bytes_per_pixel_ = DirectX::BitsPerPixel(metadata.format) / 8;
  data->resource_data_.width_ = metadata.width;
  data->resource_data_.height_ = metadata.height;
  data->resource_data_.format_ = metadata.format;
  const T_UINT32 pixels_size = (T_UINT32)image.GetPixelsSize();
  data->resource_data_.data_.resize(pixels_size);
  for (T_UINT32 i = 0; i < pixels_size; ++i)
  {
    data->resource_data_.data_[i] = image.GetPixels()[i];
  }

  return data;
}
