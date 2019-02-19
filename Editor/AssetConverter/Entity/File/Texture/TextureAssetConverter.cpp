#include "TextureAssetConverter.h"
#include <Entity/AssetMetaData.h>
#include <Native/Windows/API/Graphics/DX11/DX11Constants.h>
#include <Native/Windows/WindowsApplication.h>
#include <Native/ThirdParty/DirectXTex/DirectXTex.h>
#include <Native/ThirdParty/DirectXTex/WICTextureLoader/WICTextureLoader.h>
#include <Native/Windows/API/Graphics/DX11/DX11TextureResource.h>

using namespace Shader;

static TextureFormat TEXTURE_FORMATS[static_cast<T_FIXED_UINT8>(TextureAssetConverterSetting::ColorModel::kDataNum)][static_cast<T_FIXED_UINT8>(TextureAssetConverterSetting::CompressionQuality::kDataNum)] =
{
  { TextureFormat::kRGB, TextureFormat::kRGB_Compressed, TextureFormat::kRGB_HighQualityCompressed },
  { TextureFormat::kRGBA, TextureFormat::kRGBA_Compressed, TextureFormat::kRGBA_HighQualityCompressed },
  { TextureFormat::kHDR, TextureFormat::kHDR_Compressed, TextureFormat::kHDR_HighQualityCompressed },
};

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

  DX11TextureResource::OptimisationSetting opt_setting = DX11TextureResource::OptimisationSetting();
  
  HRESULT hr = S_FALSE;
  if (meta->GetURI().GetExtension() == "tga")
  {
    hr = DirectX::LoadFromTGAFile(wpath, &opt_setting.metadata, opt_setting.image);
  }
  else
  {
    hr = DirectX::LoadFromWICFile(wpath, 0, &opt_setting.metadata, opt_setting.image);
  }
  GG_ASSERT(SUCCEEDED(hr), "テクスチャの読み込みに失敗しました");

  opt_setting.alpha = setting->color_model == static_cast<T_FIXED_UINT8>(TextureAssetConverterSetting::ColorModel::kRGBA);
  opt_setting.convert_normal_map = setting->convert_normal_map;
  opt_setting.fade_enabled = setting->view_data.fade_enabled_;
  opt_setting.fade_end = setting->view_data.fade_end_;
  opt_setting.fade_start = setting->view_data.fade_start_;
  opt_setting.filter = DX11::TEXTURE_FILTERS[setting->view_data.filter_];
  opt_setting.format = TEXTURE_FORMATS[setting->color_model][setting->compression];
  opt_setting.max_size = setting->max_size;
  opt_setting.normal_scaling_factor = setting->normal_scaling_factor;
  opt_setting.max_levels = SIZE_MAX;

  DX11TextureResource::OptimisationResourceData(opt_setting, &data->resource_data_);

  data->view_data_ = setting->view_data;
  data->view_data_.mip_map_levels_ = (T_FIXED_UINT8)data->resource_data_.mip_map_levels_;

  return new AssetDataContainer<TextureData>(data);
}
