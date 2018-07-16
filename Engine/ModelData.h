#pragma once

#include <string>

#include "NativeType.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Color.h"
#include "Matrix4x4.h"

//=============================================================================
// MeshData
//=============================================================================
struct ModelMeshData
{
  enum VertexElement
  {
    V_ELEM_POSITION = 1 << 0,
    V_ELEM_NORMAL   = 1 << 1,
    V_ELEM_UV       = 1 << 2,
    V_ELEM_UV2      = 1 << 3,
    V_ELEM_UV3      = 1 << 4,
    V_ELEM_UV4      = 1 << 5,
    V_ELEM_TANGENT  = 1 << 6,
    V_ELEM_COLOR    = 1 << 7,
  };

  ModelMeshData() = default;
  ~ModelMeshData()
  {
    delete[] this->vertices_;
    delete[] this->normals_;
    delete[] this->uvs_;
    delete[] this->uv2s_;
    delete[] this->uv3s_;
    delete[] this->uv4s_;
    delete[] this->tangents_;
    delete[] this->colors_;
    delete[] this->indices_;
  }

  T_UINT32 vertex_count_;
  T_UINT8 vertex_format_;
  TVec3f* vertices_;
  TVec3f* normals_;
  TVec2f* uvs_;
  TVec2f* uv2s_;
  TVec2f* uv3s_;
  TVec2f* uv4s_;
  TVec3f* tangents_;
  TColor* colors_;

  T_UINT32 index_count_;
  T_UINT32* indices_;

  T_UINT8 material_index_;
};

//=============================================================================
// TextureData
//=============================================================================
struct ModelTextureData
{
  //http://assimp.sourceforge.net/lib_html/material_8h.html#a7dd415ff703a2cc53d1c22ddbbd7dde0
  enum TextureType
  {
    TEX_TYPE_NONE,
    TEX_TYPE_DIFFUSE,
    TEX_TYPE_SPECULAR,
    TEX_TYPE_AMBIENT,
    TEX_TYPE_EMISSIVE,
    TEX_TYPE_HEIGHT,
    TEX_TYPE_NORMALS,
    TEX_TYPE_SHININESS,
    TEX_TYPE_OPACITY,
    TEX_TYPE_DISPLACEMENT,
    TEX_TYPE_LIGHTMAP,
    TEX_TYPE_REFLECTION,
    TEX_TYPE_UNKNOWN,
    TEX_TYPE_DATANUM,
  };

  //http://assimp.sourceforge.net/lib_html/material_8h.html#a6186e909f1ae28133ab10f1b4635b0f9
  enum TextureMapping
  {
    TEX_MAPPING_UV,
    TEX_MAPPING_SPHERE,
    TEX_MAPPING_CYLINDER,
    TEX_MAPPING_BOX,
    TEX_MAPPING_PLANE,
    TEX_MAPPING_OTHER,
  };

  //http://assimp.sourceforge.net/lib_html/material_8h.html#afcd3096d69affba13114cedfc6f9ee6b
  enum TextureOp
  {
    TEX_OP_MUL,
    TEX_OP_ADD,
    TEX_OP_SUB,
    TEX_OP_DIV,
    TEX_OP_SMOOTH_ADD,
    TEX_OP_SIGNED_ADD,
  };

  //http://assimp.sourceforge.net/lib_html/material_8h.html#a6cbe56056751aa80e8dd714632a49de0
  enum TextureMapMode
  {
    TEX_MAP_MODE_WRAP,
    TEX_MAP_MODE_CLAMP,
    TEX_MAP_MODE_MIRROR,
    TEX_MAP_MODE_DECAL,
  };

  ModelTextureData() = default;
  ~ModelTextureData()
  {
  }

  std::string path_;
  T_UINT8 mapping_;
  T_UINT8 uv_index_;
  T_FLOAT blend_;
  T_UINT8 op_;
  T_UINT8 map_mode_;
};

//=============================================================================
// MaterialPropertyData
//=============================================================================
template <typename T>
struct ModelMaterialPropertyData
{
  ModelMaterialPropertyData() = default;
  ~ModelMaterialPropertyData()
  {
  }

  std::string name;
  T value;
};

//=============================================================================
// MaterialData
//=============================================================================
struct ModelMaterialData
{
  static std::string KEY_DIFFUSE;
  static std::string KEY_AMBIENT;
  static std::string KEY_EMISSIVE;
  static std::string KEY_BUMP;
  static std::string KEY_TRANSPARENT;
  static std::string KEY_SPECULAR;
  static std::string KEY_REFLECTION;
  static std::string KEY_POWER;

  ModelMaterialData() = default;
  ~ModelMaterialData()
  {
    for (T_UINT8 i = 0; i < ModelTextureData::TEX_TYPE_DATANUM; ++i)
    {
      for (T_UINT8 j = 0; j < this->texture_counts_[i]; ++j)
      {
        delete this->texture_datas_[i][j];
      }
      delete[] this->texture_datas_[i];
    }

    for (T_UINT8 i = 0; i < this->bool_property_count_; ++i)
    {
      delete this->bool_properties_[i];
    }
    delete[] this->bool_properties_;

    for (T_UINT8 i = 0; i < this->int_property_count_; ++i)
    {
      delete this->int_properties_[i];
    }
    delete[] this->int_properties_;

    for (T_UINT8 i = 0; i < this->float_property_count_; ++i)
    {
      delete this->float_properties_[i];
    }
    delete[] this->float_properties_;

    for (T_UINT8 i = 0; i < this->vec2_property_count_; ++i)
    {
      delete this->vec2_properties_[i];
    }
    delete[] this->vec2_properties_;

    for (T_UINT8 i = 0; i < this->vec3_property_count_; ++i)
    {
      delete this->vec3_properties_[i];
    }
    delete[] this->vec3_properties_;

    for (T_UINT8 i = 0; i < this->vec4_property_count_; ++i)
    {
      delete this->vec4_properties_[i];
    }
    delete[] this->vec4_properties_;

    for (T_UINT8 i = 0; i < this->color_property_count_; ++i)
    {
      delete this->color_properties_[i];
    }
    delete[] this->color_properties_;
    
    for (T_UINT8 i = 0; i < this->matrix_property_count_; ++i)
    {
      delete this->matrix_properties_[i];
    }
    delete[] this->matrix_properties_;
  }

  T_UINT8 texture_counts_[ModelTextureData::TEX_TYPE_DATANUM];
  ModelTextureData** texture_datas_[ModelTextureData::TEX_TYPE_DATANUM];

  T_UINT8 bool_property_count_;
  ModelMaterialPropertyData<bool>** bool_properties_;

  T_UINT8 int_property_count_;
  ModelMaterialPropertyData<T_INT32>** int_properties_;

  T_UINT8 float_property_count_;
  ModelMaterialPropertyData<T_FLOAT>** float_properties_;

  T_UINT8 vec2_property_count_;
  ModelMaterialPropertyData<TVec2f>** vec2_properties_;

  T_UINT8 vec3_property_count_;
  ModelMaterialPropertyData<TVec3f>** vec3_properties_;

  T_UINT8 vec4_property_count_;
  ModelMaterialPropertyData<TVec4f>** vec4_properties_;

  T_UINT8 color_property_count_;
  ModelMaterialPropertyData<TColor>** color_properties_;

  T_UINT8 matrix_property_count_;
  ModelMaterialPropertyData<Matrix4x4>** matrix_properties_;
};

//=============================================================================
// NodeNodeData
//=============================================================================
struct ModelNodeData
{
  ModelNodeData() = default;
  ~ModelNodeData()
  {
    for (T_UINT32 i = 0; i < this->child_count_; ++i)
    {
      delete this->children_[i];
    }
    delete[] this->children_;

    delete[] this->mesh_indices_;
  }

  TVec3f translation_;
  TVec3f scaling_;
  TVec3f rotation_;

  T_UINT32 submesh_count_;
  T_UINT32* mesh_indices_;

  T_UINT32 child_count_;
  ModelNodeData** children_;
};

//=============================================================================
// ModelData
//=============================================================================
struct ModelData
{
  ModelData() = default;
  ~ModelData()
  {
    for (T_UINT32 i = 0; i < this->material_count_; ++i)
    {
      delete this->materials_[i];
    }
    delete[] this->materials_;

    for (T_UINT32 i = 0; i < this->mesh_count_; ++i)
    {
      delete this->meshes_[i];
    }
    delete[] this->meshes_;

    delete this->root_;
  }

  ModelNodeData* root_;

  T_UINT32 material_count_;
  ModelMaterialData** materials_;
  T_UINT32 mesh_count_;
  ModelMeshData** meshes_;
};

/*
ModelData
{
  ModelNodeData* root_;

  T_UINT32 material_count_;
  ModelMaterialData** materials_;

  T_UINT32 vertex_count_;
  //GraphicsConstants‚©‚çŽæ“¾
  T_UINT32 vertex_format_;
  T_UINT32 polygon_count_;
  T_FLOAT* vertices_;

  T_UINT32 submesh_count_;
  T_UINT32* index_counts_;
  T_UINT32** indices_;
}


*/