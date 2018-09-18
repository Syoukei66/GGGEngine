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

  T_UINT32 shader_id_;
  bool protect_;
  std::unordered_map<std::string, std::shared_ptr<ShaderProperty>> properties_;

  //=============================================================================
  // Serealizer / Deserealizer
  //=============================================================================
  static MaterialData* Deserealize(const std::string& path);
  void Serealize(const std::string& path, bool test = false);

};
