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
  if (ImGui::SliderInt(u8"Fade Start", &this->selected_fade_start, 1, 12))
  {
    this->selected_fade_start = std::min(this->selected_fade_start, this->selected_fade_end);
  }
  if (ImGui::SliderInt(u8"Fade End", &this->selected_fade_end, 1, 12))
  {
    this->selected_fade_end = std::max(this->selected_fade_start, this->selected_fade_end);
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
    this->view_data.fade_start_ = this->selected_fade_start;
    this->view_data.fade_end_ = this->selected_fade_end;
    reload = true;
  }
  return reload;
}
