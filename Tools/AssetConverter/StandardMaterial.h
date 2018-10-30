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
//  inline void SetTint(const TColor& color)
//  {
//    this->SetMainColor(color);
//  }
//  inline const TColor& GetTint() const
//  {
//    return this->GetMainColor();
//  }
//
//  inline void SetAlbedoMap(const rcTexture* texture)
//  {
//    this->SetMainTexture(texture);
//  }
//  inline const rcTexture* GetAlbedoMap() const
//  {
//    return this->GetMainTexture();
//  }
//
//  inline void SetNormalMap(const rcTexture* texture)
//  {
//    this->normal_map_ = texture;
//  }
//  inline const rcTexture* GetNormalMap() const
//  {
//    return this->normal_map_;
//  }
//
//  inline void SetBumpScale(T_FLOAT bump_scale)
//  {
//    this->bump_scale_ = bump_scale;
//  }
//  inline T_FLOAT GetBumpScale() const
//  {
//    return this->bump_scale_;
//  }
//
//  inline void SetMetallicMap(const rcTexture* texture)
//  {
//    this->metallic_map_ = texture;
//  }
//  inline const rcTexture* GetMetallicMap() const
//  {
//    return this->metallic_map_;
//  }
//
//  inline void SetMetallic(T_FLOAT metallic)
//  {
//    this->metallic_ = metallic;
//  }
//  inline T_FLOAT GetMetallic() const
//  {
//    return this->metallic_;
//  }
//
//  inline void SetEmissionMap(const rcTexture* emission_map)
//  {
//    this->emission_map_ = emission_map;
//  }
//  inline const rcTexture* GetEmissionMap() const
//  {
//    return this->emission_map_;
//  }
//
//  inline void SetEmission(const TColor& emission)
//  {
//    this->emission_ = emission;
//  }
//  inline const TColor& GetEmission() const
//  {
//    return this->emission_;
//  }
//
//  inline void SetOcclusionMap(const rcTexture* emission_map)
//  {
//    this->emission_map_ = emission_map;
//  }
//  inline const rcTexture* GetOcclusionMap() const
//  {
//    return this->emission_map_;
//  }
//
//  inline void SetOcclusionStrength(T_FLOAT occlusion_strength)
//  {
//    this->occlusion_strength_ = occlusion_strength;
//  }
//  inline T_FLOAT GetOcclusionStrength() const
//  {
//    return this->occlusion_strength_;
//  }
//
//  inline void SetDetailAlbedoMap(const rcTexture* texture)
//  {
//    this->detail_albedo_map_ = texture;
//  }
//  inline const rcTexture* GetDetailAlbedoMap() const
//  {
//    return this->detail_albedo_map_;
//  }
//
//  inline void SetDetailNormalMap(const rcTexture* texture)
//  {
//    this->detail_normal_map_ = texture;
//  }
//  inline const rcTexture* GetDetailNormalMap() const
//  {
//    return this->detail_normal_map_;
//  }
//
//  inline void SetDetailBumpScale(T_FLOAT bump_scale)
//  {
//    this->detail_bump_scale_ = bump_scale;
//  }
//  inline T_FLOAT GetDetailBumpScale() const
//  {
//    return this->detail_bump_scale_;
//  }
//
//  inline void SetDetailMaskMap(const rcTexture* texture)
//  {
//    this->detail_mask_map_ = texture;
//  }
//  inline const rcTexture* GetDetailMaskMap() const
//  {
//    return this->detail_mask_map_;
//  }
//
//  inline void SetDetailTiling(const TVec2f& tiling)
//  {
//    this->detail_tiling_ = tiling;
//  }
//  inline const TVec2f& GetDetailTiling() const
//  {
//    return this->detail_tiling_;
//  }
//
//  inline void SetDetailTilingOffset(const TVec2f& offset)
//  {
//    this->detail_tiling_offset_ = offset;
//  }
//  inline const TVec2f& GetDetailTilingOffset() const
//  {
//    return this->detail_tiling_offset_;
//  }
//
//  inline void SetAlphaCutoff(T_FLOAT alpha_cutoff)
//  {
//    this->alpha_cutoff_ = alpha_cutoff;
//  }
//  inline T_FLOAT GetAlphaCutoff() const
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