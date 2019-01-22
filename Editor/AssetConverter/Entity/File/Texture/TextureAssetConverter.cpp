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
    hr = DirectX::Resize(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      width, height,
      DirectX::TEX_FILTER_DEFAULT,
      resized_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャのリサイズに失敗しました");
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
    hr = DirectX::GenerateMipMaps(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      DirectX::TEX_FILTER_DEFAULT, levels,
      mipped_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャのミップマップ作成に失敗しました");
    final_image = &mipped_image;
  }

  // ミップマップのフェードアウト設定
  // TODO: HDR画像に対応できたらした方がいいかもしれない
  DirectX::ScratchImage faded_image = DirectX::ScratchImage();
  if (setting->view_data.fade_enabled_)
  {
    std::vector<T_FLOAT> mip_gray_weights = std::vector<T_FLOAT>(levels);
    T_FLOAT start_mip_level = levels * setting->view_data.fade_start_ * 0.1f;
    T_FLOAT end_mip_level = levels * setting->view_data.fade_end_ * 0.1f;
    for (T_UINT32 i = 0; i < levels; ++i)
    {
      // start以下のミップレベルは何も行わない
      if (i <= start_mip_level)
      {
        continue;
      }
      // end以上のミップレベルはグレーアウトする
      if (i >= end_mip_level)
      {
        mip_gray_weights[i] = 1.0f;
        continue;
      }
      mip_gray_weights[i] = (i - start_mip_level) / (end_mip_level - start_mip_level);
    }

    // 色の編集が行えるようにフォーマットを固定化する
    if (DXGI_FORMAT_R8G8B8A8_UNORM != final_image->GetMetadata().format)
    {
      hr = DirectX::Convert(
        final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DX11::TEXTURE_FILTERS[setting->view_data.filter_],
        DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
        faded_image
      );
      GG_ASSERT(SUCCEEDED(hr), "テクスチャのフォーマット変換に失敗しました");
      final_image = &faded_image;
    }

    size_t bpp = DirectX::BitsPerPixel(DXGI_FORMAT_R8G8B8A8_UNORM) / 8;
    for (T_UINT32 i = 0; i < levels; ++i)
    {
      const T_FLOAT gray_weight = mip_gray_weights[i];
      const DirectX::Image* image = final_image->GetImage(i, 0, 0);
      for (T_UINT32 x = 0; x < image->width; ++x)
      {
        for (T_UINT32 y = 0; y < image->height; ++y)
        {
          T_FIXED_UINT8* pixel = &image->pixels[(image->width * y + x) * bpp];
          pixel[0] = pixel[0] + (0x80 - pixel[0]) * gray_weight;
          pixel[1] = pixel[1] + (0x80 - pixel[1]) * gray_weight;
          pixel[2] = pixel[2] + (0x80 - pixel[2]) * gray_weight;
          //pixel[3] = pixel[3] + (0x80 - pixel[3]) * gray_weight;
        }
      }
    }
  }

  // ノーマルマップに変換する
  DirectX::ScratchImage normal_image;
  if (setting->convert_normal_map)
  {
    hr = DirectX::ComputeNormalMap(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      DirectX::CNMAP_CHANNEL_RED,
      setting->normal_scaling_factor * 30.0f,
      DXGI_FORMAT_R8G8B8A8_UNORM,
      normal_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャのノーマルマップ変換に失敗しました");
    final_image = &normal_image;
  }

  // テクスチャのフォーマット変換
  DirectX::ScratchImage converted_image;
  // 圧縮フォーマットの場合、圧縮処理を行う
  if (IsCompressFormatBC1_5(format))
  {
    hr = DirectX::Compress(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      DirectX::TEX_COMPRESS_DEFAULT,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
      converted_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャの圧縮に失敗しました");
    final_image = &converted_image;

    // ブロック圧縮特有の処理
    data->resource_data_.block_size_ = 4;
  }
  // GPUアクセラレーションが使用可能な圧縮の場合それを使用する
  else if (IsCompressFormatBC6_7(format))
  {
    hr = DirectX::Compress(
      WindowsApplication::GetDX11Graphics()->GetDevice(),
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      DirectX::TEX_COMPRESS_DEFAULT,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
      converted_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャの圧縮に失敗しました");
    final_image = &converted_image;
  }
  // フォーマットが異なる場合は変換を行う
  else if (format != final_image->GetMetadata().format)
  {
    hr = DirectX::Convert(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      DX11::TEXTURE_FILTERS[setting->view_data.filter_],
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
      converted_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャのフォーマット変換に失敗しました");
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
