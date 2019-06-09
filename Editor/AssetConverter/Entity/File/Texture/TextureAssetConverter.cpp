#include "TextureAssetConverter.h"
#include <Entity/AssetMetaData.h>
#include <Native/Windows/WindowsApplication.h>Z

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

  TextureResourceOptimisationSetting opt_setting = TextureResourceOptimisationSetting();
  Application::GetPlatform()->GetGraphicsAPI()->GetTextureModule()->LoadTextureResourceData(meta->GetInputPath(), meta->GetURI().GetExtension(), &opt_setting.native_image);
  opt_setting.alpha = setting->color_model == static_cast<T_FIXED_UINT8>(TextureAssetConverterSetting::ColorModel::kRGBA);
  opt_setting.convert_normal_map = setting->convert_normal_map;
  opt_setting.fade_enabled = setting->view_data.fade_enabled_;
  opt_setting.fade_end = setting->view_data.fade_end_;
  opt_setting.fade_start = setting->view_data.fade_start_;
  opt_setting.filter = static_cast<TextureFilter>(setting->view_data.filter_);
  opt_setting.format = TEXTURE_FORMATS[setting->color_model][setting->compression];
  opt_setting.max_size = setting->max_size;
  opt_setting.normal_scaling_factor = setting->normal_scaling_factor;
  opt_setting.max_levels = SIZE_MAX;

  // ターゲットプラットフォーム側でテクスチャの最適化を行う
  Application::GetPlatform()->GetGraphicsAPI()->GetTextureModule()->OptimisationResourceData(opt_setting, &data->resource_data_);

  Application::GetPlatform()->GetGraphicsAPI()->GetTextureModule()->UnloadTextureResourceData(&opt_setting.native_image);

  data->view_data_ = setting->view_data;
  data->view_data_.mip_map_levels_ = (T_FIXED_UINT8)data->resource_data_.mip_map_levels_;

  return new AssetDataContainer<TextureData>(data);
}
