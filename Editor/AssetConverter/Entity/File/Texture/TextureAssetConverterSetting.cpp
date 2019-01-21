#include "TextureAssetConverterSetting.h"

static std::vector<const char*> TEXTURE_MAX_SIZES =
{
  "4", "8", "16", "32", "64", "128", "256", "512", "1024", "2048", "4096"
};

static std::vector<const char*> COMPRESSIONS =
{
  u8"圧縮なし", "Normal", "High", "Low"
};

static std::vector<const char*> COLOR_MODELS =
{
  "RGB", "RGBA", "HDR"
};

static std::vector<const char*> FILTERS =
{
  "Point", "Bilinear", "Trilinear"
};

static std::vector<const char*> ADDRESS =
{
  "Wrap", "Mirror", "Clamp", "Border", "MirrorOnce"
};

// =================================================================
// Methods from ConverterSetting
// =================================================================
bool TextureAssetConverterSetting::EditWithImGuiProcess()
{
  bool reload = false;
  ImGui::Combo(u8"画像最大サイズ", &this->selected_size, TEXTURE_MAX_SIZES.data(), TEXTURE_MAX_SIZES.size());
  ImGui::Combo(u8"テクスチャ圧縮", &this->selected_compression, COMPRESSIONS.data(), COMPRESSIONS.size());
  ImGui::Combo(u8"カラーモデル", &this->selected_color_model, COLOR_MODELS.data(), COLOR_MODELS.size());
  ImGui::Combo(u8"フィルタリング", &this->selected_filter, FILTERS.data(), FILTERS.size());
  ImGui::Combo(u8"Address", &this->selected_address, ADDRESS.data(), ADDRESS.size());
  ImGui::SliderInt(u8"Aniso Level", &this->selected_aniso_level, 1, 16);
  ImGui::Checkbox(u8"Fade Enabled", &this->selected_fade_enabled);
  if (this->selected_fade_enabled)
  {
    if (ImGui::SliderInt(u8"Fade Start", &this->selected_fade_start, 0, 10))
    {
      this->selected_fade_start = std::min(this->selected_fade_start, this->selected_fade_end);
    }
    if (ImGui::SliderInt(u8"Fade End", &this->selected_fade_end, 0, 10))
    {
      this->selected_fade_end = std::max(this->selected_fade_start, this->selected_fade_end);
    }
  }
  ImGui::Checkbox(u8"BumpMap To NormalMap", &this->selected_convert_normal_map);
  if (this->selected_convert_normal_map)
  {
    ImGui::DragFloat(u8"Scaling Factor", &this->selected_normal_scaling_factor, 0.1f, 0.0f, 10.0f);
  }

  if (ImGui::Button(u8"適用"))
  {
    this->max_size = std::strtol(TEXTURE_MAX_SIZES[this->selected_size], nullptr, 10);
    this->compression = this->selected_compression;
    this->color_model = this->selected_color_model;
    this->view_data.filter_ = this->selected_filter;
    this->view_data.address_u_ = this->selected_address;
    this->view_data.address_v_ = this->selected_address;
    this->view_data.aniso_level_ = this->selected_aniso_level;
    this->view_data.fade_enabled_ = this->selected_fade_enabled;
    this->view_data.fade_start_ = this->selected_fade_start;
    this->view_data.fade_end_ = this->selected_fade_end;
    this->convert_normal_map = this->selected_convert_normal_map;
    this->normal_scaling_factor = this->selected_normal_scaling_factor;
    reload = true;
  }
  return reload;
}
