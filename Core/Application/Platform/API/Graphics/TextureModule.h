#pragma once

#include <Core/Application/Platform/API/APIModuleObject.h>
#include <Core/Application/Platform/API/_Resource/TextureResource.h>

/*!
 * @brief テクスチャリソースの最適化に使用する設定
 */
struct TextureResourceOptimisationSetting
{
  void* native_image;
  bool alpha;
  size_t max_levels;
  size_t max_size;
  bool fade_enabled;
  T_UINT8 fade_start;
  T_UINT8 fade_end;
  Shader::TextureFilter filter;
  bool convert_normal_map;
  T_FLOAT normal_scaling_factor;
  Shader::TextureFormat format;
  bool use_srgb;
};

/*!
 * @brief テクスチャリソースの最適化を行うモジュール
 */
class TextureModule : public GGAPIModuleObject
{
public:
  virtual void LoadTextureResourceData(const std::string& path, const std::string& extension, void** dest) const = 0;
  virtual void UnloadTextureResourceData(void** dest) const = 0;
  virtual void OptimisationResourceData(const TextureResourceOptimisationSetting& setting, TextureResourceData* dest) const = 0;
  virtual const TextureResourceData* OptimisationResourceData(const TextureResourceData& source, TextureResourceData* dest) const = 0;
};
