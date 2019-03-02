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
  const DXGI_FORMAT format = TEXTURE_FORMATS_LINEAR[dest->format_];
  const D3D11_FILTER filter = DX11::TEXTURE_FILTERS[static_cast<T_FIXED_UINT8>(setting.filter)];

  // �����F���܂܂��t�H�[�}�b�g�̏ꍇ�͂�����l������t�B���^��
  T_UINT64 filter_flag = DirectX::TEX_FILTER_BOX;
  if (setting.alpha)
  {
    filter_flag |= DirectX::TEX_FILTER_SEPARATE_ALPHA;
  }

  // �摜��2�̗ݏ�Ƀ��T�C�Y����
  size_t width = Mathf::CalcTwoPowerValue(std::min(setting.image.GetMetadata().width, setting.max_size));
  size_t height = Mathf::CalcTwoPowerValue(std::min(setting.image.GetMetadata().height, setting.max_size));

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
    GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̃��T�C�Y�Ɏ��s���܂���");
    final_image = &resized_image;
  }

  // �~�b�v�}�b�v���쐬���鐔
  size_t levels = std::min(setting.max_levels, (size_t)std::log2(std::min(width, height)) + 1);

  // �u���b�N���k���L�̏���
  if (IsCompressFormat(format))
  {
    dest->block_size_ = 4;
    levels -= 2;
  }
  else
  {
    dest->block_size_ = 1;
  }

  // �~�b�v�}�b�v�̍쐬
  DirectX::ScratchImage mipped_image = DirectX::ScratchImage();
  if (levels > 1)
  {

    hr = DirectX::GenerateMipMaps(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      filter_flag, levels,
      mipped_image
    );
    GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̃~�b�v�}�b�v�쐬�Ɏ��s���܂���");
    final_image = &mipped_image;
  }

  // �~�b�v�}�b�v�̃t�F�[�h�A�E�g�ݒ�
  // TODO: HDR�摜�ɑΉ��ł����炵������������������Ȃ�
  DirectX::ScratchImage faded_image = DirectX::ScratchImage();
  if (setting.fade_enabled)
  {
    std::vector<T_FLOAT> mip_gray_weights = std::vector<T_FLOAT>(levels);
    T_FLOAT start_mip_level = levels * setting.fade_start * 0.1f;
    T_FLOAT end_mip_level = levels * setting.fade_end * 0.1f;
    for (T_UINT32 i = 0; i < levels; ++i)
    {
      // start�ȉ��̃~�b�v���x���͉����s��Ȃ�
      if (i <= start_mip_level)
      {
        continue;
      }
      // end�ȏ�̃~�b�v���x���̓O���[�A�E�g����
      if (i >= end_mip_level)
      {
        mip_gray_weights[i] = 1.0f;
        continue;
      }
      mip_gray_weights[i] = (i - start_mip_level) / (end_mip_level - start_mip_level);
    }

    // �F�̕ҏW���s����悤�Ƀt�H�[�}�b�g���Œ艻����
    if (DXGI_FORMAT_R8G8B8A8_UNORM != final_image->GetMetadata().format)
    {
      hr = DirectX::Convert(
        final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
        DXGI_FORMAT_R8G8B8A8_UNORM,
        filter,
        DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alpha�ɕϊ�����ۂ̂������l
        faded_image
      );
      GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̃t�H�[�}�b�g�ϊ��Ɏ��s���܂���");
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

  // �m�[�}���}�b�v�ɕϊ�����
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
    GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̃m�[�}���}�b�v�ϊ��Ɏ��s���܂���");
    final_image = &normal_image;
  }

  // �e�N�X�`���̃t�H�[�}�b�g�ϊ�
  DirectX::ScratchImage converted_image;
  // ���k�t�H�[�}�b�g�̏ꍇ�A���k�������s��
  if (IsCompressFormatBC1_5(format))
  {
    hr = DirectX::Compress(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      DirectX::TEX_COMPRESS_DEFAULT,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alpha�ɕϊ�����ۂ̂������l
      converted_image
    );
    GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̈��k�Ɏ��s���܂���");
    final_image = &converted_image;
  }
  // GPU�A�N�Z�����[�V�������g�p�\�Ȉ��k�̏ꍇ������g�p����
  else if (IsCompressFormatBC6_7(format))
  {
    hr = DirectX::Compress(
      WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice(),
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      DirectX::TEX_COMPRESS_DEFAULT,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alpha�ɕϊ�����ۂ̂������l
      converted_image
    );
    GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̈��k�Ɏ��s���܂���");
    final_image = &converted_image;
  }
  // �t�H�[�}�b�g���قȂ�ꍇ�͕ϊ����s��
  else if (format != final_image->GetMetadata().format)
  {
    hr = DirectX::Convert(
      final_image->GetImages(), final_image->GetImageCount(), final_image->GetMetadata(),
      format,
      filter,
      DirectX::TEX_THRESHOLD_DEFAULT, // 1bit alpha�ɕϊ�����ۂ̂������l
      converted_image
    );
    GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̃t�H�[�}�b�g�ϊ��Ɏ��s���܂���");
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

static const TextureResourceData* OptimisationResourceData(const TextureResourceData& data, TextureResourceData* dest)
{
  if (data.bits_per_pixel_ > 0)
  {
    return &data;
  }
  DX11TextureResource::OptimisationSetting opt_setting = DX11TextureResource::OptimisationSetting();

  opt_setting.max_size = Mathf::CalcTwoPowerValue(std::max(data.width_, data.height_));
  opt_setting.convert_normal_map = false;
  opt_setting.fade_enabled = false;
  opt_setting.filter = Shader::TextureFilter::kBilinear;
  opt_setting.format = static_cast<Shader::TextureFormat>(data.format_);
  opt_setting.alpha = Shader::HasAlpha(opt_setting.format);

  opt_setting.max_levels = data.mip_map_levels_;
  if (opt_setting.max_levels == 0)
  {
    opt_setting.max_levels = 1;
  }

  opt_setting.image.Initialize2D(
    TEXTURE_FORMATS_LINEAR[data.format_],
    data.width_, data.height_,
    1, 1  
    );
  
  // �f�[�^��image�Ɋi�[
  // TextureResource�Ƃ��Ẵf�[�^��image�Ƃ��Ẵf�[�^����
  // �P�s�N�Z��������̃o�C�g���ɍ�������ꍇ������̂ŁA
  // �������l�����Ȃ���i�[���Ă���
  const DirectX::Image* image = &opt_setting.image.GetImages()[0];
  const T_UINT8 native_byte_count = DirectX::BitsPerPixel(image->format) / 8;
  const T_UINT8 byte_count = Shader::GetBytePerPixel(static_cast<Shader::TextureFormat>(data.format_));

  for (T_UINT32 y = 0, i = 0, di = 0; y < data.height_; ++y)
  {
    for (T_UINT32 x = 0; x < data.width_; ++x)
    {
      for (T_UINT8 b = 0; b < byte_count; ++b, ++di, ++i)
      {
        image->pixels[i] = data.data_[di];
      }
      for (T_UINT8 b = 0; b < native_byte_count - byte_count; ++b, ++i)
      {
        image->pixels[i] = 0xff;
      }
    }
  }

  DX11TextureResource::OptimisationResourceData(opt_setting, dest);
  return dest;
}

// =================================================================
// Constructor / Destructor
// =================================================================
DX11TextureResource::DX11TextureResource(const TextureResourceData& data, Usage usage)
{
  ID3D11Device* device = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice();

  // �e�N�X�`�����\�[�X�̍쐬
  D3D11_TEXTURE2D_DESC texture_desc = D3D11_TEXTURE2D_DESC();
  texture_desc.Width = data.width_;
  texture_desc.Height = data.height_;
  texture_desc.MipLevels = data.mip_map_levels_;
  texture_desc.ArraySize = 1;
  texture_desc.Format = TEXTURE_FORMATS_LINEAR[data.format_];
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
    // �œK������Ă��Ȃ��f�[�^��������œK������
    TextureResourceData buf = TextureResourceData();
    const TextureResourceData* optimized = ::OptimisationResourceData(data, &buf);
    texture_desc.Width = optimized->width_;
    texture_desc.Height = optimized->height_;
    texture_desc.MipLevels = optimized->mip_map_levels_;
    texture_desc.Format = TEXTURE_FORMATS_LINEAR[optimized->format_];

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
    GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̍쐬�Ɏ��s���܂���");
  }
  else
  {
    HRESULT hr = device->CreateTexture2D(&texture_desc, nullptr, &this->resource_);
    GG_ASSERT(SUCCEEDED(hr), "�e�N�X�`���̍쐬�Ɏ��s���܂���");
  }

  this->format_ = texture_desc.Format;
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
  GG_ASSERT(SUCCEEDED(hr), "VertexBuffer�̃��b�N�Ɏ��s���܂���");

  TextureResourceData buf = TextureResourceData();
  const TextureResourceData* optimized = ::OptimisationResourceData(data, &buf);
  memcpy(mapped_subresource.pData, optimized->data_.data(), optimized->data_.size());
  context->Unmap(this->resource_, 0);
}

#endif
