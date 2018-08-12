#pragma once

#include "../Common/Bounds.h"
#include "../Common/Color.h"
#include "ModelConstants.h"

/*
  アニメーションなどのデータが削減され、
  StaticMesh１つ＋複数のマテリアルから成る
  １つのノードだけを生成するモデルデータ。

  対応形式 *は対応予定
  BlendMode
    Default
  ShadingMode 
    Flat
    Gouraud
    Phong
    *Blinn
    *OrenNayar
    *Minnaert
    *CookTorrance
    NoShading
    *Fresnel
  TextureFlag
    Alpha
    IgnoreAlpha
  MapMode
    Wrap
    Clamp
    *Decal
    Mirror
  TextureMapping
    UV
  TextureOp
    Multiply
  TextureType
    None
    Diffuse
    Specular
    *Ambient
    *Emissive
    *Height
    Normals
    *Shininess
    *Opacity
    *Displacement
    *LightMap
    *Reflection
    Unknown
*/

//=============================================================================
// MaterialData
//=============================================================================
struct StaticModelMaterialData
{
  StaticModelMaterialData() = default;
  ~StaticModelMaterialData()
  {
  }

  TColor tint_;
  T_UINT32 albedo_map_;

  T_UINT32 normal_map_;
  T_FLOAT bump_scale_;

  T_UINT32 metallic_map_;
  T_FLOAT metallic_;

  T_UINT8 smoothness_source_;
  T_FLOAT smoothness_;

  T_UINT32 emission_map_;
  TColor emission_;

  T_UINT32 occlusion_map_;
  T_FLOAT occlusion_strength_;

  TVec2f tiling_;
  TVec2f tiling_offset_;

  T_UINT32 detail_albedo_map_;
  T_UINT32 detail_normal_map_;
  T_FLOAT detail_bump_scale_;
  T_UINT32 detail_mask_map_;

  TVec2f detail_tiling_;
  TVec2f detail_tiling_offset_;

  T_FLOAT alpha_cutoff_;
};

//=============================================================================
// ModelData
//=============================================================================
struct StaticModelData
{
  StaticModelData() = default;
  ~StaticModelData()
  {
    delete[] this->data_;
    delete[] this->indices_;
    delete[] this->submesh_index_counts_;
    delete[] this->materials_;
  }

  T_UINT32 vertex_format_;
  T_UINT32 vertex_size_;
  T_UINT32 vertex_count_;
  T_FLOAT* data_;

  T_UINT32 polygon_count_;

  T_UINT32 index_count_;
  T_UINT32* indices_;

  T_UINT8 submesh_count_;
  T_UINT32* submesh_index_counts_;
  T_UINT8* submesh_material_indices_;

  Bounds bounds_;

  T_UINT8 material_count_;
  StaticModelMaterialData* materials_;
};
