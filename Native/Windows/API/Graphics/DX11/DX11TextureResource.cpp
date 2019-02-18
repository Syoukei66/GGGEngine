#include "DX11TextureResource.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/API/Graphics/DX11/DX11Constants.h>
#include <Native/Windows/WindowsApplication.h>
#include <Native/ThirdParty/DirectXTex/WICTextureLoader/WICTextureLoader.h>

#pragma comment(lib, "DirectXTex.lib")

UniqueRef<rcTextureResource> rcTextureResource::Create(const TextureResourceData& data, Usage usage)
{
  return UniqueRef<rcTextureResource>(new DX11TextureResource(data, usage));
}

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

void DX11TextureResource::OptimisationResourceData(const OptimisationSetting& setting, TextureResourceData* dest)
{
  dest->format_ = static_cast<T_FIXED_UINT8>(setting.format);
  DXGI_FORMAT format = TEXTURE_FORMATS_LINEAR[dest->format_];

  // 透明色が含まれるフォーマットの場合はそれを考慮するフィルタに
  T_UINT64 filter_flag = DirectX::TEX_FILTER_BOX;
  if (setting.alpha)
  {
    filter_flag |= DirectX::TEX_FILTER_SEPARATE_ALPHA;
  }

  // 画像を2の累乗にリサイズする
  size_t width = Mathf::CalcTwoPowerValue(std::min(setting.metadata.width, setting.max_size));
  size_t height = Mathf::CalcTwoPowerValue(std::min(setting.metadata.height, setting.max_size));

  const DirectX::ScratchImage* final_image = &setting.image;

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
  size_t levels = (size_t)std::log2(std::min(width, height)) + 1;

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
        setting.filter,
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
      setting.filter,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alphaに変換する際のしきい値
      converted_image
    );
    GG_ASSERT(SUCCEEDED(hr), "テクスチャのフォーマット変換に失敗しました");
    final_image = &converted_image;
  }

  dest->bits_per_pixel_ = (T_FIXED_UINT8)(DirectX::BitsPerPixel(format));
  dest->width_ = (T_FIXED_UINT16)width;
  dest->height_ = (T_FIXED_UINT16)height;
  dest->format_ = format;
  const T_UINT32 pixels_size = (T_UINT32)final_image->GetPixelsSize();
  dest->data_.resize(pixels_size);
  for (T_UINT32 i = 0; i < pixels_size; ++i)
  {
    dest->data_[i] = final_image->GetPixels()[i];
  }

  dest->mip_map_levels_ = (T_FIXED_UINT8)levels;
}

static const TextureResourceData* OptimisationResourceData(const TextureResourceData& data, TextureResourceData* dest)
{
  if (data.bits_per_pixel_ > 0)
  {
    return &data;
  }
  DX11TextureResource::OptimisationSetting opt_setting = DX11TextureResource::OptimisationSetting();

  DX11TextureResource::OptimisationResourceData(opt_setting, dest);
  return dest;
}

// =================================================================
// Constructor / Destructor
// =================================================================
DX11TextureResource::DX11TextureResource(const TextureResourceData& data, Usage usage)
{
  ID3D11Device* device = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice();

  this->format_ = static_cast<DXGI_FORMAT>(data.format_);

  // テクスチャリソースの作成
  D3D11_TEXTURE2D_DESC texture_desc = D3D11_TEXTURE2D_DESC();
  texture_desc.Width = data.width_;
  texture_desc.Height = data.height_;
  texture_desc.MipLevels = data.mip_map_levels_;
  texture_desc.ArraySize = 1;
  texture_desc.Format = this->format_;
  texture_desc.SampleDesc.Count = 1;
  texture_desc.SampleDesc.Quality = 0;
  if (usage == Usage::kImmutable)
  {
    texture_desc.Usage = D3D11_USAGE_IMMUTABLE;
    texture_desc.CPUAccessFlags = 0;
  }
  else if (usage == Usage::kUltraDynamic)
  {
    texture_desc.Usage = D3D11_USAGE_DYNAMIC;
    texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  }
  texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  texture_desc.MiscFlags = 0;

  if (data.data_.size() > 0)
  {
    // 最適化されていないデータだったら最適化する
    TextureResourceData buf = TextureResourceData();
    const TextureResourceData* optimized = ::OptimisationResourceData(data, &buf);

    std::vector<D3D11_SUBRESOURCE_DATA> initial_datas = std::vector<D3D11_SUBRESOURCE_DATA>(optimized->mip_map_levels_);
    T_FIXED_UINT16 width = optimized->width_;
    T_FIXED_UINT16 height = optimized->height_;
    T_UINT64 offset = 0;
    for (T_UINT8 i = 0; i < optimized->mip_map_levels_; ++i)
    {
      D3D11_SUBRESOURCE_DATA initial_data = D3D11_SUBRESOURCE_DATA();
      initial_data.pSysMem = &optimized->data_[offset];
      initial_data.SysMemPitch = (width * optimized->block_size_ * optimized->bits_per_pixel_) / 8;
      initial_data.SysMemSlicePitch = 0;
      initial_datas[i] = initial_data;
      offset += (width * height * optimized->bits_per_pixel_) / 8;
      width = width >> 1;
      height = height >> 1;
    }
    HRESULT hr = device->CreateTexture2D(&texture_desc, &initial_datas[0], &this->resource_);
    GG_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");
  }
  else
  {
    HRESULT hr = device->CreateTexture2D(&texture_desc, nullptr, &this->resource_);
    GG_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");
  }

}

DX11TextureResource::~DX11TextureResource()
{
  this->resource_->Release();
}

// =================================================================
// Methods from rcTextureResource
// =================================================================
void DX11TextureResource::UpdateSubresource(const TextureResourceData& data, Usage usage)
{
  ID3D11DeviceContext* context = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetImmediateContext();
  D3D11_MAPPED_SUBRESOURCE mapped_subresource = D3D11_MAPPED_SUBRESOURCE();
  HRESULT hr = context->Map(this->resource_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
  GG_ASSERT(SUCCEEDED(hr), "VertexBufferのロックに失敗しました");

  TextureResourceData buf = TextureResourceData();
  const TextureResourceData* optimized = ::OptimisationResourceData(data, &buf);
  unsigned char* p = (unsigned char*)mapped_subresource.pData;

  std::vector<D3D11_SUBRESOURCE_DATA> initial_datas = std::vector<D3D11_SUBRESOURCE_DATA>(optimized->mip_map_levels_);
  T_UINT64 size = optimized->data_.size();
  for (T_UINT64 i = 0; i < size; ++i)
  {
    p[i] = optimized->data_[i];
  }
  context->Unmap(this->resource_, 0);
}

#endif
