#pragma once

#include <memory>
#include <unordered_map>
#include "ShaderProperties.h"

struct MaterialData
{
  MaterialData() = default;
  ~MaterialData()
  {
  }

  T_UINT32 shader_unique_id_;
  bool protect_;
  T_UINT32 main_tex_unique_id_;
  TColor color_;
  TVec2f tiling_;
  TVec2f tiling_offset_;
  bool billbording_;

  std::unordered_map<std::string, T_UINT32> texture_properties_;
  std::unordered_map<std::string, std::shared_ptr<ShaderProperty>> properties_;

  //=============================================================================
  // Serealizer / Deserealizer
  //=============================================================================
  static MaterialData* Deserealize(const std::string& path);
  void Serealize(const std::string& path, bool test = false);

};
