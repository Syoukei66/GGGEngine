#pragma once

#include <vector>
#include "Material.h"

class StandardMaterial : public Material
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  StandardMaterial(INativeShader* resource, bool protect = false);
  virtual ~StandardMaterial();

  // =================================================================
  // Methods
  // =================================================================
protected:
  virtual Material* CreateClone(INativeShader* shader) override;
  virtual void CopyPropertiesToClone(Material* clone) override;

public:
  virtual void SetProperties(INativeShader* shader) override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetTint(const TColor& color)
  {
    this->SetMainColor(color);
  }
  inline const TColor& GetTint() const
  {
    return this->GetMainColor();
  }

  inline void SetAlbedoMap(const Texture* texture)
  {
    this->SetMainTexture(texture);
  }
  inline const Texture* GetAlbedoMap() const
  {
    return this->GetMainTexture();
  }

  inline void SetNormalMap(const Texture* texture)
  {
    this->normal_map_ = texture;
  }
  inline const Texture* GetNormalMap() const
  {
    return this->normal_map_;
  }

  inline void SetBumpScale(T_FLOAT bump_scale)
  {
    this->bump_scale_ = bump_scale;
  }
  inline T_FLOAT GetBumpScale() const
  {
    return this->bump_scale_;
  }

  inline void SetMetallicMap(const Texture* texture)
  {
    this->metallic_map_ = texture;
  }
  inline const Texture* GetMetallicMap() const
  {
    return this->metallic_map_;
  }

  inline void SetMetallic(T_FLOAT metallic)
  {
    this->metallic_ = metallic;
  }
  inline T_FLOAT GetMetallic() const
  {
    return this->metallic_;
  }

  inline void SetEmissionMap(const Texture* emission_map)
  {
    this->emission_map_ = emission_map;
  }
  inline const Texture* GetEmissionMap() const
  {
    return this->emission_map_;
  }

  inline void SetEmission(const TColor& emission)
  {
    this->emission_ = emission;
  }
  inline const TColor& GetEmission() const
  {
    return this->emission_;
  }

  inline void SetOcclusionMap(const Texture* emission_map)
  {
    this->emission_map_ = emission_map;
  }
  inline const Texture* GetOcclusionMap() const
  {
    return this->emission_map_;
  }

  inline void SetOcclusionStrength(T_FLOAT occlusion_strength)
  {
    this->occlusion_strength_ = occlusion_strength;
  }
  inline T_FLOAT GetOcclusionStrength() const
  {
    return this->occlusion_strength_;
  }

  inline void SetDetailAlbedoMap(const Texture* texture)
  {
    this->detail_albedo_map_ = texture;
  }
  inline const Texture* GetDetailAlbedoMap() const
  {
    return this->detail_albedo_map_;
  }

  inline void SetDetailNormalMap(const Texture* texture)
  {
    this->detail_normal_map_ = texture;
  }
  inline const Texture* GetDetailNormalMap() const
  {
    return this->detail_normal_map_;
  }

  inline void SetDetailBumpScale(T_FLOAT bump_scale)
  {
    this->detail_bump_scale_ = bump_scale;
  }
  inline T_FLOAT GetDetailBumpScale() const
  {
    return this->detail_bump_scale_;
  }

  inline void SetDetailMaskMap(const Texture* texture)
  {
    this->detail_mask_map_ = texture;
  }
  inline const Texture* GetDetailMaskMap() const
  {
    return this->detail_mask_map_;
  }

  inline void SetDetailTiling(const TVec2f& tiling)
  {
    this->detail_tiling_ = tiling;
  }
  inline const TVec2f& GetDetailTiling() const
  {
    return this->detail_tiling_;
  }

  inline void SetDetailTilingOffset(const TVec2f& offset)
  {
    this->detail_tiling_offset_ = offset;
  }
  inline const TVec2f& GetDetailTilingOffset() const
  {
    return this->detail_tiling_offset_;
  }

  inline void SetAlphaCutoff(T_FLOAT alpha_cutoff)
  {
    this->alpha_cutoff_ = alpha_cutoff;
  }
  inline T_FLOAT GetAlphaCutoff() const
  {
    return this->alpha_cutoff_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const Texture* normal_map_;
  T_FLOAT bump_scale_;

  const Texture* metallic_map_;
  T_FLOAT metallic_;

  const Texture* emission_map_;
  TColor emission_;

  const Texture* occlusion_map_;
  T_FLOAT occlusion_strength_;

  const Texture* detail_albedo_map_;
  const Texture* detail_normal_map_;
  T_FLOAT detail_bump_scale_;
  const Texture* detail_mask_map_;

  TVec2f detail_tiling_;
  TVec2f detail_tiling_offset_;

  T_FLOAT alpha_cutoff_;
};