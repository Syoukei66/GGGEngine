#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Native/ThirdParty/DirectXTex/DirectXTex.h>
#include <Core/Application/Platform/API/_Resource/TextureResource.h>

class DX11TextureResource : public rcTextureResource
{
public:
  struct OptimisationSetting
  {
    DirectX::ScratchImage image;
    DirectX::TexMetadata metadata;
    bool alpha;
    size_t max_levels;
    size_t max_size;
    bool fade_enabled;
    T_UINT8 fade_start;
    T_UINT8 fade_end;
    D3D11_FILTER filter;
    bool convert_normal_map;
    T_FLOAT normal_scaling_factor;
    Shader::TextureFormat format;
  };

  /*!
   * @brief テクスチャリソースデータの最適化を行う
   */
  static void OptimisationResourceData(const OptimisationSetting& setting, TextureResourceData* dest);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11TextureResource(const TextureResourceData& data, Usage usage);
  ~DX11TextureResource();

  // =================================================================
  // Methods from rcTextureResource
  // =================================================================
public:
  virtual void UpdateSubresource(const TextureResourceData& data, Usage usage) override;

  // =================================================================
  // Data Members
  // =================================================================
public:
  DXGI_FORMAT GetFormat() const
  {
    return this->format_;
  }

  ID3D11Texture2D* GetResource() const
  {
    return this->resource_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3D11Texture2D* resource_;
  DXGI_FORMAT format_;

};

#endif
