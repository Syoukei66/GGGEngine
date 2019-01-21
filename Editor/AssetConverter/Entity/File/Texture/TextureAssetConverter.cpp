#include "TextureAssetConverter.h"
#include <Entity/AssetMetaData.h>
#include <DirectXTex.h>
#include <Editor/ThirdParty/DirectXTex/WICTextureLoader/WICTextureLoader.h>
#include <Native/Windows/API/Graphics/DX11/DX11Constants.h>
#include <Native/Windows/WindowsApplication.h>

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

bool IsCompressFormatBC1_5(DXGI_FORMAT format)
{
  return format == DXGI_FORMAT_BC1_UNORM ||
    format == DXGI_FORMAT_BC1_UNORM_SRGB ||
    format == DXGI_FORMAT_BC2_UNORM ||
    format == DXGI_FORMAT_BC2_UNORM_SRGB ||
    format == DXGI_FORMAT_BC3_UNORM ||
    format == DXGI_FORMAT_BC3_UNORM_SRGB ||
    format == DXGI_FORMAT_BC4_UNORM ||
    format == DXGI_FORMAT_BC4_SNORM ||
    format == DXGI_FORMAT_BC5_UNORM ||
    format == DXGI_FORMAT_BC5_SNORM;
}

bool IsCompressFormatBC6_7(DXGI_FORMAT format)
{
  return format == DXGI_FORMAT_BC6H_SF16 ||
    format == DXGI_FORMAT_BC6H_UF16 ||
    format == DXGI_FORMAT_BC7_UNORM ||
    format == DXGI_FORMAT_BC7_UNORM_SRGB;
}

bool IsCompressFormat(DXGI_FORMAT format)
{
  return IsCompressFormatBC1_5(format) || IsCompressFormatBC6_7(format);
}

// =================================================================
// Methods from AssetConverter
// =================================================================
IAssetDataContainer* TextureAssetConverter::ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const
{
  TextureData* data = new TextureData();

  AssetMetaData* meta = entity->GetMetaData();
  TextureAssetConverterSetting* setting = static_cast<TextureAssetConverterSetting*>(meta->GetConverterSetting().get());

  WCHAR	wpath[256] = {};

  errno_t err = 0;

  //ロケール指定
  setlocale(LC_ALL, "japanese");
  //変換
  err = (errno_t)mbstowcs(wpath, meta->GetInputPath().c_str(), sizeof(wpath));
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

  DirectX::ScratchImage* final_image = &image;

  // 画像を2の累乗にリサイズする
  size_t width = Mathf::CalcTwoPowerValue(std::min(metadata.width, (size_t)setting->max_size));
  size_t height = Mathf::CalcTwoPowerValue(std::min(metadata.height, (size_t)setting->max_size));

  DirectX::ScratchImage resized_image;
  if (metadata.width != width || metadata.height != height)
  {
    DirectX::Resize(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      width, height,
      DirectX::TEX_FILTER_DEFAULT,
      resized_image
    );
    final_image = &resized_image;
  }
  
  // ミップマップを作成する数
  size_t levels = (size_t)std::log2(std::min(width, height)) + 1;

  // ブロック圧縮特有の処理
  if (IsCompressFormat(format))
  {
    data->resource_data_.block_size_ = 4;
    levels -= 2;
  }

  // ミップマップの作成
  DirectX::ScratchImage mipped_image = DirectX::ScratchImage();
  if (levels > 1)
  {
    DirectX::GenerateMipMaps(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      DirectX::TEX_FILTER_DEFAULT, levels,
      mipped_image
    );
    final_image = &mipped_image;
  }

  DirectX::ScratchImage converted_image;
  // 圧縮形式だったら圧縮を行う
  if (IsCompressFormatBC1_5(format))
  {
    DirectX::Compress(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      DirectX::TEX_COMPRESS_DEFAULT,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
      converted_image
    );
    final_image = &converted_image;

    // ブロック圧縮特有の処理
    data->resource_data_.block_size_ = 4;
  }
  // GPUアクセラレーションが使用可能な圧縮の場合それを使用する
  else if (IsCompressFormatBC6_7(format))
  {
    DirectX::Compress(
      WindowsApplication::GetDX11Graphics()->GetDevice(),
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      DirectX::TEX_COMPRESS_DEFAULT,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
      converted_image
    );
    final_image = &converted_image;
  }
  else if (format != metadata.format)
  {
    DirectX::Convert(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      DX11::TEXTURE_FILTERS[setting->view_data.filter_],
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
      converted_image
    );
    final_image = &converted_image;
  }

  data->resource_data_.bits_per_pixel_ = (T_FIXED_UINT8)(DirectX::BitsPerPixel(format));
  data->resource_data_.width_ = (T_FIXED_UINT16)width;
  data->resource_data_.height_ = (T_FIXED_UINT16)height;
  data->resource_data_.format_ = format;
  const T_UINT32 pixels_size = (T_UINT32)final_image->GetPixelsSize();
  data->resource_data_.data_.resize(pixels_size);
  for (T_UINT32 i = 0; i < pixels_size; ++i)
  {
    data->resource_data_.data_[i] = final_image->GetPixels()[i];
  }

  data->view_data_ = setting->view_data;
  data->view_data_.mip_map_levels_ = (T_FIXED_UINT8)levels;
  data->resource_data_.mip_map_levels_ = data->view_data_.mip_map_levels_;

  return new AssetDataContainer<TextureData>(data);
}
