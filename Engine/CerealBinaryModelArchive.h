#pragma once

#include "ModelData.h"
#include "Cereal\types\string.hpp"
#include "Cereal\archives\binary.hpp"

#define SAFE_NEW(var, value) if (!var)\
{\
  var = new value();\
}\

template <class Archive>
void serialize(Archive& archive, TVec2f& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 2));
}

template <class Archive>
void serialize(Archive& archive, TVec3f& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 3));
}

template <class Archive>
void serialize(Archive& archive, TVec4f& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 4));
}

template <class Archive>
void serialize(Archive& archive, TColor& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 4));
}

template <class Archive>
void serialize(Archive& archive, Matrix4x4& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 16));
}

//=============================================================================
// MeshData
//=============================================================================
template <class Archive>
void serialize(Archive& archive, ModelMeshData& data)
{
  archive(data.vertex_count_);
  archive(data.vertex_format_);

  //position
  if (data.vertex_format_ & ModelMeshData::V_ELEM_POSITION)
  {
    SAFE_NEW(data.vertices_, TVec3f[data.vertex_count_]);
    archive(cereal::binary_data(data.vertices_, sizeof(TVec3f) * data.vertex_count_));
  }

  //normal
  if (data.vertex_format_ & ModelMeshData::V_ELEM_NORMAL)
  {
    SAFE_NEW(data.normals_, TVec3f[data.vertex_count_]);
    archive(cereal::binary_data(data.normals_, sizeof(TVec3f) * data.vertex_count_));
  }

  //uv
  if (data.vertex_format_ & ModelMeshData::V_ELEM_UV)
  {
    SAFE_NEW(data.uvs_, TVec2f[data.vertex_count_]);
    archive(cereal::binary_data(data.uvs_, sizeof(TVec2f) * data.vertex_count_));
  }

  //uv2
  if (data.vertex_format_ & ModelMeshData::V_ELEM_UV2)
  {
    SAFE_NEW(data.uv2s_, TVec2f[data.vertex_count_]);
    archive(cereal::binary_data(data.uv2s_, sizeof(TVec2f) * data.vertex_count_));
  }

  //uv3
  if (data.vertex_format_ & ModelMeshData::V_ELEM_UV3)
  {
    SAFE_NEW(data.uv3s_, TVec2f[data.vertex_count_]);
    archive(cereal::binary_data(data.uv3s_, sizeof(TVec2f) * data.vertex_count_));
  }

  //uv4
  if (data.vertex_format_ & ModelMeshData::V_ELEM_UV4)
  {
    SAFE_NEW(data.uv4s_, TVec2f[data.vertex_count_]);
    archive(cereal::binary_data(data.uv4s_, sizeof(TVec2f) * data.vertex_count_));
  }

  //tangent
  if (data.vertex_format_ & ModelMeshData::V_ELEM_TANGENT)
  {
    SAFE_NEW(data.tangents_, TVec3f[data.vertex_count_]);
    archive(cereal::binary_data(data.tangents_, sizeof(TVec3f) * data.vertex_count_));
  }

  //color
  if (data.vertex_format_ & ModelMeshData::V_ELEM_COLOR)
  {
    SAFE_NEW(data.colors_, TColor[data.vertex_count_]);
    archive(cereal::binary_data(data.colors_, sizeof(TColor) * data.vertex_count_));
  }

  archive(data.index_count_);
  if (data.index_count_ > 0)
  {
    SAFE_NEW(data.indices_, T_UINT32[data.index_count_]);
    archive(cereal::binary_data(data.indices_, sizeof(T_UINT32) * data.index_count_));
  }
}

//=============================================================================
// TextureData
//=============================================================================
template <class Archive>
void serialize(Archive& archive, ModelTextureData& data)
{
  archive(
    data.path_,
    data.mapping_,
    data.uv_index_,
    data.blend_,
    data.op_,
    data.map_mode_
  );
}

//=============================================================================
// MaterialPropertyData
//=============================================================================
template <class Archive>
void serialize(Archive& archive, ModelMaterialPropertyData<bool>& data)
{
  archive(data.name, data.value);
}

template <class Archive>
void serialize(Archive& archive, ModelMaterialPropertyData<T_INT32>& data)
{
  archive(data.name, data.value);
}

template <class Archive>
void serialize(Archive& archive, ModelMaterialPropertyData<T_FLOAT>& data)
{
  archive(data.name, data.value);
}

template <class Archive>
void serialize(Archive& archive, ModelMaterialPropertyData<TVec2f>& data)
{
  archive(data.name, data.value);
}

template <class Archive>
void serialize(Archive& archive, ModelMaterialPropertyData<TVec3f>& data)
{
  archive(data.name, data.value);
}

template <class Archive>
void serialize(Archive& archive, ModelMaterialPropertyData<TVec4f>& data)
{
  archive(data.name, data.value);
}

template <class Archive>
void serialize(Archive& archive, ModelMaterialPropertyData<TColor>& data)
{
  archive(data.name, data.value);
}

template <class Archive>
void serialize(Archive& archive, ModelMaterialPropertyData<Matrix4x4>& data)
{
  archive(data.name, data.value);
}

//=============================================================================
// MaterialData
//=============================================================================
template <class Archive>
void serialize(Archive& archive, ModelMaterialData& data)
{
  for (T_UINT8 i = 0; i < ModelTextureData::TEX_TYPE_DATANUM; ++i)
  {
    archive(data.texture_counts_[i]);
    if (data.texture_counts_[i] == 0)
    {
      continue;
    }
    SAFE_NEW(data.texture_datas_[i], ModelTextureData*[data.texture_counts_[i]]);
    for (T_UINT8 j = 0; j < data.texture_counts_[i]; ++j)
    {
      SAFE_NEW(data.texture_datas_[i][j], ModelTextureData);
      archive(*data.texture_datas_[i][j]);
    }
  }

  //bool
  archive(data.bool_property_count_);
  if (data.bool_property_count_ > 0)
  {
    SAFE_NEW(data.bool_properties_, ModelMaterialPropertyData<bool>*[data.bool_property_count_]);
    for (T_UINT8 i = 0; i < data.bool_property_count_; ++i)
    {
      SAFE_NEW(data.bool_properties_[i], ModelMaterialPropertyData<bool>);
      archive(*data.bool_properties_[i]);
    }
  }

  //T_INT32
  archive(data.int_property_count_);
  if (data.int_property_count_ > 0)
  {
    SAFE_NEW(data.int_properties_, ModelMaterialPropertyData<T_INT32>*[data.int_property_count_]);
    for (T_UINT8 i = 0; i < data.int_property_count_; ++i)
    {
      SAFE_NEW(data.int_properties_[i], ModelMaterialPropertyData<T_INT32>);
      archive(*data.int_properties_[i]);
    }
  }

  //T_FLOAT
  archive(data.float_property_count_);
  if (data.float_property_count_ > 0)
  {
    SAFE_NEW(data.float_properties_, ModelMaterialPropertyData<T_FLOAT>*[data.float_property_count_]);
    for (T_UINT8 i = 0; i < data.float_property_count_; ++i)
    {
      SAFE_NEW(data.float_properties_[i], ModelMaterialPropertyData<T_FLOAT>);
      archive(*data.float_properties_[i]);
    }
  }

  //TVec2f
  archive(data.vec2_property_count_);
  if (data.vec2_property_count_ > 0)
  {
    SAFE_NEW(data.vec2_properties_, ModelMaterialPropertyData<TVec2f>*[data.vec2_property_count_]);
    for (T_UINT8 i = 0; i < data.vec2_property_count_; ++i)
    {
      SAFE_NEW(data.vec2_properties_[i], ModelMaterialPropertyData<TVec2f>);
      archive(*data.vec2_properties_[i]);
    }
  }

  //TVec3f
  archive(data.vec3_property_count_);
  if (data.vec3_property_count_ > 0)
  {
    SAFE_NEW(data.vec3_properties_, ModelMaterialPropertyData<TVec3f>*[data.vec3_property_count_]);
    for (T_UINT8 i = 0; i < data.vec3_property_count_; ++i)
    {
      SAFE_NEW(data.vec3_properties_[i], ModelMaterialPropertyData<TVec3f>);
      archive(*data.vec3_properties_[i]);
    }
  }

  //TVec4f
  archive(data.vec4_property_count_);
  if (data.vec4_property_count_ > 0)
  {
    SAFE_NEW(data.vec4_properties_, ModelMaterialPropertyData<TVec4f>*[data.vec4_property_count_]);
    for (T_UINT8 i = 0; i < data.vec4_property_count_; ++i)
    {
      SAFE_NEW(data.vec4_properties_[i], ModelMaterialPropertyData<TVec4f>);
      archive(*data.vec4_properties_[i]);
    }
  }

  //TColor
  archive(data.color_property_count_);
  if (data.color_property_count_ > 0)
  {
    SAFE_NEW(data.color_properties_, ModelMaterialPropertyData<TColor>*[data.color_property_count_]);
    for (T_UINT8 i = 0; i < data.color_property_count_; ++i)
    {
      SAFE_NEW(data.color_properties_[i], ModelMaterialPropertyData<TColor>);
      archive(*data.color_properties_[i]);
    }
  }

  //Matrix4x4
  archive(data.matrix_property_count_);
  if (data.matrix_property_count_ > 0)
  {
    SAFE_NEW(data.matrix_properties_, ModelMaterialPropertyData<Matrix4x4>*[data.matrix_property_count_]);
    for (T_UINT8 i = 0; i < data.matrix_property_count_; ++i)
    {
      SAFE_NEW(data.matrix_properties_[i], ModelMaterialPropertyData<Matrix4x4>);
      archive(*data.matrix_properties_[i]);
    }
  }
}

//=============================================================================
// NodeData
//=============================================================================
template <class Archive>
void serialize(Archive& archive, ModelNodeData& data)
{
  archive(
    data.translation_,
    data.scaling_,
    data.rotation_
  );
  archive(data.submesh_count_);
  if (data.submesh_count_ > 0)
  {
    SAFE_NEW(data.mesh_indices_, T_UINT32[data.submesh_count_]);
    archive(cereal::binary_data(data.mesh_indices_, sizeof(T_UINT32) * data.submesh_count_));
  }
  archive(data.child_count_);
  if (data.child_count_ > 0)
  {
    SAFE_NEW(data.children_, ModelNodeData*[data.child_count_]);
    for (T_UINT32 i = 0; i < data.child_count_; ++i)
    {
      SAFE_NEW(data.children_[i], ModelNodeData);
      archive(*data.children_[i]);
    }
  }
}

//=============================================================================
// ModelNodeData
//=============================================================================
template <class Archive>
void serialize(Archive& archive, ModelData& data)
{
  SAFE_NEW(data.root_, ModelNodeData);
  archive(*data.root_);

  archive(data.material_count_);
  if (data.material_count_ > 0)
  {
    SAFE_NEW(data.materials_, ModelMaterialData*[data.material_count_]);
    for (T_INT32 i = 0; i < data.material_count_; ++i)
    {
      SAFE_NEW(data.materials_[i], ModelMaterialData);
      archive(*data.materials_[i]);
    }
  }

  archive(data.mesh_count_);
  if (data.mesh_count_ > 0)
  {
    SAFE_NEW(data.meshes_, ModelMeshData*[data.mesh_count_]);
    for (T_INT32 i = 0; i < data.mesh_count_; ++i)
    {
      SAFE_NEW(data.meshes_[i], ModelMeshData);
      archive(*data.meshes_[i]);
    }
  }
}
