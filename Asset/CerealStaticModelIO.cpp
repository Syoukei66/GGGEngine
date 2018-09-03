#include "..\Core\StaticMeshData.h"
#include "CerealStaticModelIO.h"

#include "../Core/CerealStructArchive.hpp"
#include "../Core/CerealArchiveMacro.hpp"
#include "../Core/CerealIO.h"
#include "../Core/NativeAssert.h"

#include "StaticModelData.h"

//=============================================================================
// MaterialData
//=============================================================================
template <class Archive>
void serialize(Archive& archive, StaticModelMaterialData& value)
{
  archive(value.tint_);
  archive(value.albedo_map_);

  archive(value.normal_map_);
  archive(value.bump_scale_);

  archive(value.metallic_map_);
  archive(value.metallic_);

  archive(value.smoothness_source_);
  archive(value.smoothness_);

  archive(value.emission_map_);
  archive(value.emission_);

  archive(value.occlusion_map_);
  archive(value.occlusion_strength_);

  archive(value.tiling_);
  archive(value.tiling_offset_);

  archive(value.detail_albedo_map_);
  archive(value.detail_normal_map_);
  archive(value.detail_bump_scale_);
  archive(value.detail_mask_map_);

  archive(value.detail_tiling_);
  archive(value.detail_tiling_offset_);

  archive(value.alpha_cutoff_);

}

//=============================================================================
// ModelData
//=============================================================================
template <class Archive>
void serialize(Archive& archive, StaticModelData& value)
{
  archive(value.vertex_format_);
  archive(value.vertex_size_);
  archive(value.vertex_count_);
  SAFE_NEW(value.data_, T_FLOAT[value.vertex_count_ * value.vertex_size_]);
  archive(cereal::binary_data(value.data_, sizeof(T_FLOAT) * value.vertex_count_ * value.vertex_size_));
  archive(value.polygon_count_);
  archive(value.index_count_);
  SAFE_NEW(value.indices_, T_UINT32[value.index_count_]);
  archive(cereal::binary_data(value.indices_, sizeof(T_UINT32) * value.index_count_));
  archive(value.submesh_count_);
  SAFE_NEW(value.submesh_index_counts_, T_UINT32[value.submesh_count_]);
  archive(cereal::binary_data(value.submesh_index_counts_, sizeof(T_UINT32) * value.submesh_count_));
  SAFE_NEW(value.submesh_material_indices_, T_UINT8[value.submesh_count_]);
  archive(cereal::binary_data(value.submesh_material_indices_, sizeof(T_UINT8) * value.submesh_count_));
  archive(value.bounds_);
  archive(value.material_count_);
  SAFE_NEW(value.materials_, StaticModelMaterialData[value.material_count_]);
  for (T_UINT8 i = 0; i < value.material_count_; ++i)
  {
    archive(value.materials_[i]);
  }
}

//=============================================================================
// IO
//=============================================================================
StaticModelData* ModelIO::StaticModel::Import(const std::string& path)
{
  return CerealIO::Binary::Import<StaticModelData>(path.c_str());
}

void ModelIO::StaticModel::Export(const std::string& path, StaticModelData* data)
{
  CerealIO::Binary::Export<StaticModelData>(path.c_str(), data);
}
