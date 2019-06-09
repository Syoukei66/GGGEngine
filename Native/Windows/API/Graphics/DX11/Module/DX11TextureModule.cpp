#include "DX11TextureModule.h"

#if GG_GRAPHICS_API_DX11

#include <Native/ThirdParty/DirectXTex/WICTextureLoader/WICTextureLoader.h>
#include <Native/Windows/WindowsApplication.h>
#include <Native/Windows/API/Graphics/DX11/DX11Constants.h>

#pragma comment(lib, "DirectXTex.lib")

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL(DX11TextureModule)
{
  return true;
}

// =================================================================
// Methods from TextureModule
// =================================================================
void DX11TextureModule::LoadTextureResourceData(const std::string& path, const std::string& extension, void** dest) const
{
  WCHAR	wpath[256] = {};

  errno_t err = 0;

  //ロケール指定
  setlocale(LC_ALL, "japanese");
  //変換
  err = (errno_t)mbstowcs(wpath, path.c_str(), sizeof(wpath));

  TextureResourceOptimisationSetting opt_setting = TextureResourceOptimisationSetting();

  HRESULT hr = S_FALSE;
  DirectX::ScratchImage* image = new DirectX::ScratchImage();
  if (extension == "tga")
  {
    hr = DirectX::LoadFromTGAFile(wpath, nullptr, *image);
  }
  else
  {
    hr = DirectX::LoadFromWICFile(wpath, 0, nullptr, *image);
  }
  GG_ASSERT(SUCCEEDED(hr), "テクスチャの読み込みに失敗しました");

  (*dest) = image;
}

void DX11TextureModule::UnloadTextureResourceData(void** dest) const
{
  delete (DirectX::ScratchImage*)(*dest);
}

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

void DX11TextureModule::OptimisationResourceData(const TextureResourceOptimisationSetting& setting, TextureResourceData* dest) const
{
  dest->format_ = static_cast<T_FIXED_UINT8>(setting.format);
  const DXGI_FORMAT format = this->GetTextureFormat(dest->format_, setting.use_srgb);
  const D3D11_FILTER filter = DX11::TEXTURE_FILTERS[static_cast<T_FIXED_UINT8>(setting.filter)];

  // 透明色が含まれるフォーマットの場合はそれを考慮するフィルタに
  T_UINT64 filter_flag = DirectX::TEX_FILTER_BOX;
  if (setting.alpha)
  {
    filter_flag |= DirectX::TEX_FILTER_SEPARATE_ALPHA;
  }

  // 画像を2の累乗にリサイズする
  const DirectX::ScratchImage* image = (const DirectX::ScratchImage*)setting.native_image;

  size_t width = Mathf::CalcTwoPowerValue(std::min(image->GetMetadata().width, setting.max_size));
  size_t height = Mathf::CalcTwoPowerValue(std::min(image->GetMetadata().height, setting.max_size));

  const DirectX::ScratchImage* final_image = image;

  HRESULT hr = S_FALSE;
  DirectX::ScratchImage resized_image;
  if (final_image->GetMetadata().width != width || final_image->GetMetadata().height != height)
  {
    hr = DirectX::Resize(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      width, height,
      filter_flag,
      resized_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャのリサイズに失敗しました");
    final_image = &resized_image;
  }

  // ミップマップを作成する数
  size_t levels = std::min(setting.max_levels, (size_t)std::log2(std::min(width, height)) + 1);

  // ブロック圧縮特有の処理
  if (IsCompressFormat(format))
  {
    dest->block_size_ = 4;
    levels -= 2;
  }
  else
  {
    dest->block_size_ = 1;
  }

  // ミップマップの作成
  DirectX::ScratchImage mipped_image = DirectX::ScratchImage();
  if (levels > 1)
  {

    hr = DirectX::GenerateMipMaps(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      filter_flag, levels,
      mipped_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャのミップマップ作成に失敗しました");
    final_image = &mipped_image;
  }

  // ミップマップのフェードアウト設定
  // TODO: HDR画像に対応できたらした方がいいかもしれない
  DirectX::ScratchImage faded_image = DirectX::ScratchImage();
  if (setting.fade_enabled)
  {
    std::vector<T_FLOAT> mip_gray_weights = std::vector<T_FLOAT>(levels);
    T_FLOAT start_mip_level = levels * setting.fade_start * 0.1f;
    T_FLOAT end_mip_level = levels * setting.fade_end * 0.1f;
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
        filter,
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
          pixel[0] = (T_FIXED_UINT8)(pixel[0] + (0x80 - pixel[0]) * gray_weight);
          pixel[1] = (T_FIXED_UINT8)(pixel[1] + (0x80 - pixel[1]) * gray_weight);
          pixel[2] = (T_FIXED_UINT8)(pixel[2] + (0x80 - pixel[2]) * gray_weight);
          //pixel[3] = pixel[3] + (0x80 - pixel[3]) * gray_weight;
        }
      }
    }
  }

  // ノーマルマップに変換する
  DirectX::ScratchImage normal_image;
  if (setting.convert_normal_map)
  {
    hr = DirectX::ComputeNormalMap(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      DirectX::CNMAP_CHANNEL_RED,
      setting.normal_scaling_factor * 30.0f,
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
  }
  // GPUアクセラレーションが使用可能な圧縮の場合それを使用する
  else if (IsCompressFormatBC6_7(format))
  {
    hr = DirectX::Compress(
      WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice(),
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
      filter,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
      converted_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャのフォーマット変換に失敗しました");
    final_image = &converted_image;
  }

  dest->bits_per_pixel_ = (T_FIXED_UINT8)(DirectX::BitsPerPixel(format));
  dest->width_ = (T_FIXED_UINT16)width;
  dest->height_ = (T_FIXED_UINT16)height;
  const T_UINT32 pixels_size = (T_UINT32)final_image->GetPixelsSize();
  dest->data_.resize(pixels_size);
  for (T_UINT32 i = 0; i < pixels_size; ++i)
  {
    dest->data_[i] = final_image->GetPixels()[i];
  }

  dest->mip_map_levels_ = (T_FIXED_UINT8)levels;
}

const TextureResourceData* DX11TextureModule::OptimisationResourceData(const TextureResourceData& data, TextureResourceData* dest) const
{
  if (data.bits_per_pixel_ > 0)
  {
    return &data;
  }
  TextureResourceOptimisationSetting opt_setting = TextureResourceOptimisationSetting();

  opt_setting.max_size = Mathf::CalcTwoPowerValue(std::max(data.width_, data.height_));
  opt_setting.convert_normal_map = false;
  opt_setting.fade_enabled = false;
  opt_setting.filter = Shader::TextureFilter::kBilinear;
  opt_setting.format = static_cast<Shader::TextureFormat>(data.format_);
  opt_setting.alpha = Shader::HasAlpha(opt_setting.format);
  opt_setting.use_srgb = false;

  opt_setting.max_levels = data.mip_map_levels_;
  if (opt_setting.max_levels == 0)
  {
    opt_setting.max_levels = 1;
  }

  DirectX::ScratchImage* image = new DirectX::ScratchImage();
  image->Initialize2D(
    this->GetTextureFormat(data.format_, false),
    data.width_, data.height_,
    1, 1
  );

  // データをfinal_imageに格納
  // TextureResourceとしてのデータとimageとしてのデータだと
  // １ピクセルあたりのバイト数に差がある場合があるので、
  // そこを考慮しながら格納していく
  const DirectX::Image* final_image = &image->GetImages()[0];
  const T_UINT8 native_byte_count = DirectX::BitsPerPixel(final_image->format) / 8;
  const T_UINT8 byte_count = Shader::GetBytePerPixel(static_cast<Shader::TextureFormat>(data.format_));

  for (T_UINT32 y = 0, i = 0, di = 0; y < data.height_; ++y)
  {
    for (T_UINT32 x = 0; x < data.width_; ++x)
    {
      for (T_UINT8 b = 0; b < byte_count; ++b, ++di, ++i)
      {
        final_image->pixels[i] = data.data_[di];
      }
      for (T_UINT8 b = 0; b < native_byte_count - byte_count; ++b, ++i)
      {
        final_image->pixels[i] = 0xff;
      }
    }
  }

  opt_setting.native_image = image;
  
  this->OptimisationResourceData(opt_setting, dest);

  return dest;
}

// =================================================================
// Methods
// =================================================================
static DXGI_FORMAT TEXTURE_FORMATS_LINEAR[static_cast<T_FIXED_UINT8>(Shader::TextureFormat::DATANUM)] =
{
  // RGB
  DXGI_FORMAT_R8G8B8A8_UNORM,
  DXGI_FORMAT_BC1_UNORM,
  DXGI_FORMAT_BC7_UNORM,

  // RGBA
  DXGI_FORMAT_R8G8B8A8_UNORM,
  DXGI_FORMAT_BC3_UNORM,
  DXGI_FORMAT_BC7_UNORM,

  // HDR
  DXGI_FORMAT_R16G16B16A16_FLOAT,
  DXGI_FORMAT_BC6H_UF16,
  DXGI_FORMAT_BC6H_UF16,

  // Depth
  DXGI_FORMAT_D32_FLOAT,
  DXGI_FORMAT_D16_UNORM,
  DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
  DXGI_FORMAT_D24_UNORM_S8_UINT,

  // Height
  DXGI_FORMAT_R16_UNORM,
  DXGI_FORMAT_R8_UNORM,
  DXGI_FORMAT_R32_FLOAT,
};

static DXGI_FORMAT TEXTURE_FORMATS_SRGB[static_cast<T_FIXED_UINT8>(Shader::TextureFormat::DATANUM)] =
{
  // RGB
  DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
  DXGI_FORMAT_BC1_UNORM_SRGB,
  DXGI_FORMAT_BC7_UNORM_SRGB,

  // RGBA
  DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
  DXGI_FORMAT_BC3_UNORM_SRGB,
  DXGI_FORMAT_BC7_UNORM_SRGB,

  // HDR
  DXGI_FORMAT_R16G16B16A16_FLOAT,
  DXGI_FORMAT_BC6H_UF16,
  DXGI_FORMAT_BC6H_UF16,

  // Depth
  DXGI_FORMAT_D32_FLOAT,
  DXGI_FORMAT_D16_UNORM,
  DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
  DXGI_FORMAT_D24_UNORM_S8_UINT,

  // Height
  DXGI_FORMAT_R16_UNORM,
  DXGI_FORMAT_R8_UNORM,
  DXGI_FORMAT_R32_FLOAT,
};

DXGI_FORMAT DX11TextureModule::GetTextureFormat(T_FIXED_UINT8 format, bool use_srgb) const
{
  if (use_srgb)
  {
    return TEXTURE_FORMATS_SRGB[format];
  }
  return TEXTURE_FORMATS_LINEAR[format];
}

#endif