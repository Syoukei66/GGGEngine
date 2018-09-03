#include "StandardMaterial.h"

StandardMaterial::StandardMaterial(rcShader* resource, bool protect)
  : rcMaterial(resource, protect)
{
}

StandardMaterial::~StandardMaterial()
{
}

rcMaterial* StandardMaterial::CreateClone(rcShader* shader)
{
  return new StandardMaterial(shader);
}

void StandardMaterial::CopyPropertiesToClone(rcMaterial* clone)
{
  StandardMaterial* ret = (StandardMaterial*)clone;
  ret->SetTint(this->GetTint());
  ret->SetAlbedoMap(this->GetAlbedoMap());

  ret->SetNormalMap(this->GetNormalMap());
  ret->SetBumpScale(this->GetBumpScale());

  ret->SetMetallicMap(this->GetMetallicMap());
  ret->SetMetallic(this->GetMetallic());

  ret->SetEmissionMap(this->GetEmissionMap());
  ret->SetEmission(this->GetEmission());

  ret->SetOcclusionMap(this->GetOcclusionMap());
  ret->SetOcclusionStrength(this->GetOcclusionStrength());

  ret->SetDetailAlbedoMap(this->GetDetailAlbedoMap());
  ret->SetDetailNormalMap(this->GetDetailNormalMap());
  ret->SetDetailBumpScale(this->GetDetailBumpScale());
  ret->SetDetailMaskMap(this->GetDetailMaskMap());

  ret->SetDetailTiling(this->GetDetailTiling());
  ret->SetDetailTilingOffset(this->GetDetailTilingOffset());

  ret->SetAlphaCutoff(this->GetAlphaCutoff());
}

void StandardMaterial::SetProperties(rcShader* shader)
{
  shader->SetTexture("_NormalMap", this->normal_map_);
  shader->SetFloat("_BumpScale", this->bump_scale_);

  shader->SetTexture("_MetallicMap", this->metallic_map_);
  shader->SetFloat("_Metallic", this->metallic_);

  shader->SetTexture("_EmissionMap", this->emission_map_);
  shader->SetColor("_Emission", this->emission_);

  shader->SetTexture("_OcclusionMap", this->occlusion_map_);
  shader->SetFloat("_OcclusionStrength", this->occlusion_strength_);

  shader->SetTexture("_DetailAlbedoMap", this->detail_albedo_map_);
  shader->SetTexture("_DetailNormalMap", this->detail_normal_map_);
  shader->SetFloat("_DetailBumpScale", this->detail_bump_scale_);
  shader->SetTexture("_DetailMaskMap", this->detail_mask_map_);

  shader->SetVec2f("_DetailTiling", this->detail_tiling_);
  shader->SetVec2f("_DetailTilingOffset", this->detail_tiling_offset_);

  shader->SetFloat("_AlphaCutoff", this->alpha_cutoff_);
}
