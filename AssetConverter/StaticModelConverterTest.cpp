#include "StaticModelConverterTest.h"
#include "ConverterTestMacro.hpp"

void StaticModelConverterTest::Compare(const StaticModelData& a, const StaticModelData& b)
{
  PushState("StaticModelData");
  COMPARE_ATTR(vertex_format_);
  COMPARE_ATTR(vertex_size_);
  COMPARE_ATTR(vertex_count_);
  COMPARE_ATTRS(data_, vertex_count_ * a.vertex_size_);
  COMPARE_ATTR(polygon_count_);
  COMPARE_ATTR(index_count_);
  COMPARE_ATTRS(indices_, index_count_);
  COMPARE_ATTR(submesh_count_);
  COMPARE_ATTRS(submesh_index_counts_, submesh_count_);
  COMPARE_ATTRS(submesh_material_indices_, submesh_count_);
  COMPARE_ATTR(bounds_);
  COMPARE_ATTR(material_count_);
  COMPARE_ATTRS(materials_, material_count_);
  PopState();
}

void StaticModelConverterTest::Compare(const StaticModelMaterialData& a, const StaticModelMaterialData& b)
{
  PushState("StaticModelMaterialData");
  COMPARE_ATTR(tint_);
  COMPARE_ATTR(albedo_map_);

  COMPARE_ATTR(normal_map_);
  COMPARE_ATTR(bump_scale_);

  COMPARE_ATTR(metallic_map_);
  COMPARE_ATTR(metallic_);

  COMPARE_ATTR(smoothness_source_);
  COMPARE_ATTR(smoothness_);

  COMPARE_ATTR(emission_map_);
  COMPARE_ATTR(emission_);

  COMPARE_ATTR(occlusion_map_);
  COMPARE_ATTR(occlusion_strength_);

  COMPARE_ATTR(tiling_);
  COMPARE_ATTR(tiling_offset_);

  COMPARE_ATTR(detail_albedo_map_);
  COMPARE_ATTR(detail_normal_map_);
  COMPARE_ATTR(detail_bump_scale_);
  COMPARE_ATTR(detail_mask_map_);

  COMPARE_ATTR(detail_tiling_);
  COMPARE_ATTR(detail_tiling_offset_);

  COMPARE_ATTR(alpha_cutoff_);
  PopState();
}
