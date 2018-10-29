//#pragma once
//
//#include <vector>
//#include "../Core/Material.h"
//
//class StandardMaterial : public rcMaterial
//{
//  // =================================================================
//  // Constructor / Destructor
//  // =================================================================
//public:
//  StandardMaterial(rcShader* resource, bool protect = false);
//  virtual ~StandardMaterial();
//
//  // =================================================================
//  // Methods
//  // =================================================================
//protected:
//  virtual rcMaterial* CreateClone(rcShader* shader) override;
//  virtual void CopyPropertiesToClone(rcMaterial* clone) override;
//
//public:
//  virtual void SetProperties(rcShader* shader) override;
//
//  // =================================================================
//  // Setter / Getter
//  // =================================================================
//public:
//  GG_INLINE void SetTint(const TColor& color)
//  {
//    this->SetMainColor(color);
//  }
//  GG_INLINE const TColor& GetTint() const
//  {
//    return this->GetMainColor();
//  }
//
//  GG_INLINE void SetAlbedoMap(const rcTexture* texture)
//  {
//    this->SetMainTexture(texture);
//  }
//  GG_INLINE const rcTexture* GetAlbedoMap() const
//  {
//    return this->GetMainTexture();
//  }
//
//  GG_INLINE void SetNormalMap(const rcTexture* texture)
//  {
//    this->normal_map_ = texture;
//  }
//  GG_INLINE const rcTexture* GetNormalMap() const
//  {
//    return this->normal_map_;
//  }
//
//  GG_INLINE void SetBumpScale(T_FLOAT bump_scale)
//  {
//    this->bump_scale_ = bump_scale;
//  }
//  GG_INLINE T_FLOAT GetBumpScale() const
//  {
//    return this->bump_scale_;
//  }
//
//  GG_INLINE void SetMetallicMap(const rcTexture* texture)
//  {
//    this->metallic_map_ = texture;
//  }
//  GG_INLINE const rcTexture* GetMetallicMap() const
//  {
//    return this->metallic_map_;
//  }
//
//  GG_INLINE void SetMetallic(T_FLOAT metallic)
//  {
//    this->metallic_ = metallic;
//  }
//  GG_INLINE T_FLOAT GetMetallic() const
//  {
//    return this->metallic_;
//  }
//
//  GG_INLINE void SetEmissionMap(const rcTexture* emission_map)
//  {
//    this->emission_map_ = emission_map;
//  }
//  GG_INLINE const rcTexture* GetEmissionMap() const
//  {
//    return this->emission_map_;
//  }
//
//  GG_INLINE void SetEmission(const TColor& emission)
//  {
//    this->emission_ = emission;
//  }
//  GG_INLINE const TColor& GetEmission() const
//  {
//    return this->emission_;
//  }
//
//  GG_INLINE void SetOcclusionMap(const rcTexture* emission_map)
//  {
//    this->emission_map_ = emission_map;
//  }
//  GG_INLINE const rcTexture* GetOcclusionMap() const
//  {
//    return this->emission_map_;
//  }
//
//  GG_INLINE void SetOcclusionStrength(T_FLOAT occlusion_strength)
//  {
//    this->occlusion_strength_ = occlusion_strength;
//  }
//  GG_INLINE T_FLOAT GetOcclusionStrength() const
//  {
//    return this->occlusion_strength_;
//  }
//
//  GG_INLINE void SetDetailAlbedoMap(const rcTexture* texture)
//  {
//    this->detail_albedo_map_ = texture;
//  }
//  GG_INLINE const rcTexture* GetDetailAlbedoMap() const
//  {
//    return this->detail_albedo_map_;
//  }
//
//  GG_INLINE void SetDetailNormalMap(const rcTexture* texture)
//  {
//    this->detail_normal_map_ = texture;
//  }
//  GG_INLINE const rcTexture* GetDetailNormalMap() const
//  {
//    return this->detail_normal_map_;
//  }
//
//  GG_INLINE void SetDetailBumpScale(T_FLOAT bump_scale)
//  {
//    this->detail_bump_scale_ = bump_scale;
//  }
//  GG_INLINE T_FLOAT GetDetailBumpScale() const
//  {
//    return this->detail_bump_scale_;
//  }
//
//  GG_INLINE void SetDetailMaskMap(const rcTexture* texture)
//  {
//    this->detail_mask_map_ = texture;
//  }
//  GG_INLINE const rcTexture* GetDetailMaskMap() const
//  {
//    return this->detail_mask_map_;
//  }
//
//  GG_INLINE void SetDetailTiling(const TVec2f& tiling)
//  {
//    this->detail_tiling_ = tiling;
//  }
//  GG_INLINE const TVec2f& GetDetailTiling() const
//  {
//    return this->detail_tiling_;
//  }
//
//  GG_INLINE void SetDetailTilingOffset(const TVec2f& offset)
//  {
//    this->detail_tiling_offset_ = offset;
//  }
//  GG_INLINE const TVec2f& GetDetailTilingOffset() const
//  {
//    return this->detail_tiling_offset_;
//  }
//
//  GG_INLINE void SetAlphaCutoff(T_FLOAT alpha_cutoff)
//  {
//    this->alpha_cutoff_ = alpha_cutoff;
//  }
//  GG_INLINE T_FLOAT GetAlphaCutoff() const
//  {
//    return this->alpha_cutoff_;
//  }
//
//  // =================================================================
//  // Data Member
//  // =================================================================
//private:
//  const rcTexture* normal_map_;
//  T_FLOAT bump_scale_;
//
//  const rcTexture* metallic_map_;
//  T_FLOAT metallic_;
//
//  const rcTexture* emission_map_;
//  TColor emission_;
//
//  const rcTexture* occlusion_map_;
//  T_FLOAT occlusion_strength_;
//
//  const rcTexture* detail_albedo_map_;
//  const rcTexture* detail_normal_map_;
//  T_FLOAT detail_bump_scale_;
//  const rcTexture* detail_mask_map_;
//
//  TVec2f detail_tiling_;
//  TVec2f detail_tiling_offset_;
//
//  T_FLOAT alpha_cutoff_;
//};