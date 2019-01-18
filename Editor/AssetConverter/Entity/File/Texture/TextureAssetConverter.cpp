#include "TextureAssetConverter.h"
#include <Entity/AssetMetaData.h>
#include <DirectXTex.h>
#include <Editor/ThirdParty/DirectXTex/WICTextureLoader/WICTextureLoader.h>
#include <Native/Windows/API/Graphics/DX11/DX11Constants.h>

#pragma comment(lib, "DirectXTex.lib")

static DXGI_FORMAT TEXTURE_FORMATS_LINEAR[static_cast<T_FIXED_UINT8>(TextureAssetConverterSetting::ColorModel::kDataNum)][static_cast<T_FIXED_UINT8>(TextureAssetConverterSetting::CompressionQuality::kDataNum)] =
{
  { DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_BC7_UNORM, DXGI_FORMAT_BC1_UNORM },
  { DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_BC3_UNORM, DXGI_FORMAT_BC7_UNORM, DXGI_FORMAT_BC3_UNORM },
  { DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_BC6H_UF16, DXGI_FORMAT_BC6H_UF16, DXGI_FORMAT_BC6H_UF16 },
};

static DXGI_FORMAT TEXTURE_FORMATS_SRGB[static_cast<T_FIXED_UINT8>(TextureAssetConverterSetting::ColorModel::kDataNum)][static_cast<T_FIXED_UINT8>(TextureAssetConverterSetting::CompressionQuality::kDataNum)] =
{
  { DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGI_FORMAT_BC1_UNORM_SRGB, DXGI_FORMAT_BC7_UNORM_SRGB, DXGI_FORMAT_BC1_UNORM_SRGB },
  { DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGI_FORMAT_BC3_UNORM_SRGB, DXGI_FORMAT_BC7_UNORM_SRGB, DXGI_FORMAT_BC3_UNORM_SRGB },
  { DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_BC6H_UF16, DXGI_FORMAT_BC6H_UF16, DXGI_FORMAT_BC6H_UF16 },
};

// =================================================================
// Methods from AssetConverter
// =================================================================
IAssetDataContainer* TextureAssetConverter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const
{
  TextureData* data = new TextureData();

  TextureAssetConverterSetting* setting = static_cast<TextureAssetConverterSetting*>(meta->GetConverterSetting().get());

  ID3D11Resource* texture;
  ID3D11ShaderResourceView* shader_resource_view;

  WCHAR	wpath[256] = {};

  errno_t err = 0;

  //ロケール指定
  setlocale(LC_ALL, "japanese");
  //変換
  err = mbstowcs(wpath, meta->GetInputPath().c_str(), sizeof(wpath));
  DirectX::TexMetadata metadata = DirectX::TexMetadata();
  DirectX::ScratchImage image = DirectX::ScratchImage();

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

  DXGI_FORMAT format = TEXTURE_FORMATS_LINEAR[setting->color_model][setting->compression];

  DirectX::ScratchImage converted_image;
  DirectX::Compress(
    image.GetImages(), image.GetImageCount(), metadata,
    format, 
    DX11::TEXTURE_FILTERS[setting->view_data.filter_], 
    DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
    converted_image
  );

  data->resource_data_.bytes_per_pixel_ = DirectX::BitsPerPixel(metadata.format) / 8;
  data->resource_data_.width_ = metadata.width;
  data->resource_data_.height_ = metadata.height;
  data->resource_data_.format_ = format;
  const T_UINT32 pixels_size = (T_UINT32)converted_image.GetPixelsSize();
  data->resource_data_.data_.resize(pixels_size);
  for (T_UINT32 i = 0; i < pixels_size; ++i)
  {
    data->resource_data_.data_[i] = converted_image.GetPixels()[i];
  }

  data->view_data_ = setting->view_data;

  return new AssetDataContainer<TextureData>(data, this);
}
