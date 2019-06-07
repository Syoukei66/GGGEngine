#pragma once

#if GG_GRAPHICS_API_DX11

#include <Native/ThirdParty/DirectXTex/DirectXTex.h>

/*!
 * @brief テクスチャリソースの最適化を行うモジュール
 */
class DX11TextureModule : public TextureModule
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(DX11TextureModule);
  GG_CREATE_FUNC(DX11TextureModule) { return true; }

  // =================================================================
  // Methods from TextureModule
  // =================================================================
public:
  virtual void LoadTextureResourceData(const std::string& path, const std::string& extension, void** dest) const override;
  virtual void UnloadTextureResourceData(void** dest) const override;
  virtual void OptimisationResourceData(const TextureResourceOptimisationSetting& setting, TextureResourceData* dest) const override;
  virtual const TextureResourceData* OptimisationResourceData(const TextureResourceData& data, TextureResourceData* dest) const override;

  // =================================================================
  // Methods
  // =================================================================
public:
  DXGI_FORMAT GetTextureFormat(T_FIXED_UINT8 format, bool use_srgb) const;

};

#endif