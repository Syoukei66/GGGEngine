#include "StaticModelConverterTest.h"
#include "ConverterTestMacro.hpp"

void StaticModelConverterTest::Compare(const StaticModelData& a, const StaticModelData& b)
{
  PushState("StaticModelData");
  COMPARE_ATTR(vertex_format_);
  COMPARE_ATTR(vertex_size_);
  COMPARE_ATTR(vertex_count_);
  COMPARE_ATTRS(vertices_, vertex_count_);
  COMPARE_ATTR(polygon_count_);
  COMPARE_ATTR(index_count_);
  COMPARE_ATTRS(indices_, index_count_);
  COMPARE_ATTR(submesh_count_);
  COMPARE_ATTRS(submesh_index_counts_, submesh_count_);
  COMPARE_ATTR(bounds_);
  COMPARE_ATTR(material_count_);
  COMPARE_ATTRS(materials_, material_count_);
  PopState();
}

void StaticModelConverterTest::Compare(const StaticModelTextureData& a, const StaticModelTextureData& b)
{
  PushState("StaticModelTextureData");
  COMPARE_ATTR(unique_id_);
  COMPARE_ATTR(uv_index_);
  COMPARE_ATTR(flags_);
  COMPARE_ATTR(map_mode_);
  COMPARE_ATTR(type_);
  PopState();
}

void StaticModelConverterTest::Compare(const StaticModelMaterialData& a, const StaticModelMaterialData& b)
{
  PushState("StaticModelMaterialData");
  COMPARE_ATTR(opacity_);
  COMPARE_ATTR(shininess_);
  COMPARE_ATTR(shininess_strength_);
  COMPARE_ATTR(color_count_);
  COMPARE_ATTRS(color_types_, color_count_);
  COMPARE_ATTRS(colors_, color_count_);
  COMPARE_ATTR(texture_count_);
  COMPARE_ATTRS(texture_datas_, texture_count_);
  COMPARE_ATTR(shading_mode_);
  COMPARE_ATTR(twosided_);
  PopState();
}
