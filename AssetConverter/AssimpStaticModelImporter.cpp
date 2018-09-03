#include "AssimpStaticModelImporter.h"
#include <assimp\mesh.h>

#include "../Core/GraphicsConstants.h"
#include "../Core/NativeAssert.h"
#include "../Core/Color.h"

#include "AssetManager.h"

#include "AssimpMathImporter.h"
#include "AssimpMaterialSystemImporter.h"

namespace ModelImporter
{

namespace Assimp
{
static T_UINT32 ImportTexture(AssetInfo* info, const aiMaterial* material, aiTextureType type)
{
  aiString path;
  aiTextureMapping mapping;
  T_UINT32 uv_index;
  T_FLOAT blend;
  aiTextureOp op;
  aiTextureMapMode map_mode;
  T_UINT32 flags;

  T_UINT32 ret = 0;
  for (T_UINT8 i = 0; i < 8; ++i)
  {
    if (AI_SUCCESS == aiGetMaterialTexture(material, type, i, &path, &mapping, &uv_index, &blend, &op, &map_mode, &flags))
    {
      NATIVE_ASSERT(ret == 0, "テクスチャが想定していたより多いです");
      const std::string full_path = info->directory_path + path.C_Str();
      info->meta_data->references.emplace(full_path);
      ret = OldAssetManager::GetInstance().GetInfomation(full_path)->meta_data->unique_id;
    }
  }
  return ret;
}

//=============================================================================
// MaterialData
//=============================================================================
static void ImportMaterial(AssetInfo* info, const aiMaterial* material, StaticModelMaterialData* dest)
{
  using namespace ModelConstants;

  //Colors
  aiColor4D color;
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
  {
    dest->tint_ = ToTColor(color);
  }
  dest->albedo_map_ = ImportTexture(info, material, aiTextureType_DIFFUSE);

  dest->normal_map_ = ImportTexture(info, material, aiTextureType_NORMALS);
  aiGetMaterialFloat(material, AI_MATKEY_BUMPSCALING, &dest->bump_scale_);

  dest->metallic_map_ = ImportTexture(info, material, aiTextureType_SPECULAR);
  aiGetMaterialFloat(material, "mat.metallic", 0, 0, &dest->metallic_);

  dest->smoothness_source_ = 0;
  aiGetMaterialFloat(material, "mat.smoothness", 0, 0, &dest->smoothness_);

  dest->emission_map_ = ImportTexture(info, material, aiTextureType_EMISSIVE);
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
  {
    dest->emission_ = ToTColor(color);
  }

  dest->occlusion_map_ = ImportTexture(info, material, aiTextureType_LIGHTMAP);
  aiGetMaterialFloat(material, "mat.occlusion_strength", 0, 0, &dest->smoothness_);

  dest->tiling_ = TVec2f(1.0f, 1.0f);
  dest->tiling_offset_ = TVec2f(0.0f, 0.0f);

  dest->detail_albedo_map_ = 0;
  dest->detail_normal_map_ = 0;
  dest->detail_bump_scale_ = 0.0f;
  dest->detail_mask_map_ = 0;

  dest->detail_tiling_ = TVec2f(1.0f, 1.0f);
  dest->detail_tiling_offset_ = TVec2f(0.0f, 0.0f);

  dest->alpha_cutoff_ = 0.0f;
}

//=============================================================================
// ModelData
//=============================================================================
StaticModelData* ImportStaticModel(AssetInfo* info, const aiScene* scene)
{
  NATIVE_ASSERT(scene->mNumMeshes == scene->mNumMaterials, "思ってたのと違う");

  //参照をクリア
  info->meta_data->references.clear();

  StaticModelData* ret = new StaticModelData();

  using namespace Graphics;

  ret->submesh_count_ = scene->mNumMeshes;
  ret->submesh_index_counts_ = new T_UINT32[ret->submesh_count_]();
  ret->submesh_material_indices_ = new T_UINT8[ret->submesh_count_]();
  //
  for (T_UINT32 m = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];
    ret->vertex_count_ += mesh->mNumVertices;
    ret->polygon_count_ += mesh->mNumFaces;
    for (T_UINT32 f = 0, ii = 0; f < mesh->mNumFaces; ++f)
    {
      ret->index_count_ += mesh->mFaces[f].mNumIndices;
      ret->submesh_index_counts_[m] += mesh->mFaces[f].mNumIndices;
      ret->submesh_material_indices_[m] = mesh->mMaterialIndex;
    }

    if (!(ret->vertex_format_ & V_ATTR_POSITION) && mesh->HasPositions())
    {
      ret->vertex_format_ |= V_ATTR_POSITION;
      ret->vertex_size_ += V_ATTRSIZE_POSITION;
    }

    if (!(ret->vertex_format_ & V_ATTR_NORMAL) && mesh->HasNormals())
    {
      ret->vertex_format_ |= V_ATTR_NORMAL;
      ret->vertex_size_ += V_ATTRSIZE_NORMAL;
    }

    if (!(ret->vertex_format_ & V_ATTR_UV) && mesh->HasTextureCoords(0))
    {
      ret->vertex_format_ |= V_ATTR_UV;
      ret->vertex_size_ += V_ATTRSIZE_UV;
    }

    if (!(ret->vertex_format_ & V_ATTR_UV2) && mesh->HasTextureCoords(1))
    {
      ret->vertex_format_ |= V_ATTR_UV2;
      ret->vertex_size_ += V_ATTRSIZE_UV2;
    }

    if (!(ret->vertex_format_ & V_ATTR_UV3) && mesh->HasTextureCoords(2))
    {
      ret->vertex_format_ |= V_ATTR_UV3;
      ret->vertex_size_ += V_ATTRSIZE_UV3;
    }

    if (!(ret->vertex_format_ & V_ATTR_UV4) && mesh->HasTextureCoords(3))
    {
      ret->vertex_format_ |= V_ATTR_UV4;
      ret->vertex_size_ += V_ATTRSIZE_UV4;
    }

    if (!(ret->vertex_format_ & V_ATTR_TANGENT) && mesh->HasTangentsAndBitangents())
    {
      ret->vertex_format_ |= V_ATTR_TANGENT;
      ret->vertex_size_ += V_ATTRSIZE_TANGENT;
    }

    if (!(ret->vertex_format_ & V_ATTR_COLOR) && mesh->HasVertexColors(0))
    {
      ret->vertex_format_ |= V_ATTR_COLOR;
      ret->vertex_size_ += V_ATTRSIZE_COLOR;
    }
  }

  TVec3f min = { 0.0f, 0.0f, 0.0f };
  TVec3f max = { 0.0f, 0.0f, 0.0f };

  //
  ret->data_ = new unsigned char[ret->vertex_count_ * ret->vertex_size_]();
  ret->indices_ = new T_UINT32[ret->index_count_]();
  unsigned char* p = ret->data_;
  for (T_UINT32 m = 0, ii = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];

    //
    for (T_UINT32 v = 0; v < mesh->mNumVertices; ++v)
    {
      //mesh
      if (ret->vertex_format_ & V_ATTR_POSITION)
      {
        T_FLOAT* vertex = (T_FLOAT*)p;
        vertex[0] = mesh->mVertices[v].x;
        vertex[1] = mesh->mVertices[v].y;
        vertex[2] = mesh->mVertices[v].z;
        p += V_ATTRSIZE_POSITION;

        min.x = std::min(min.x, mesh->mVertices[v].x);
        min.y = std::min(min.y, mesh->mVertices[v].y);
        min.z = std::min(min.z, mesh->mVertices[v].z);

        max.x = std::max(max.x, mesh->mVertices[v].x);
        max.y = std::max(max.y, mesh->mVertices[v].y);
        max.z = std::max(max.z, mesh->mVertices[v].z);
      }
      if (ret->vertex_format_ & V_ATTR_NORMAL)
      {
        T_FLOAT* normal = (T_FLOAT*)p;
        normal[0] = mesh->mNormals[v].x;
        normal[1] = mesh->mNormals[v].y;
        normal[2] = mesh->mNormals[v].z;
        p += V_ATTRSIZE_NORMAL;
      }
      if (ret->vertex_format_ & V_ATTR_UV)
      {
        T_FLOAT* uv = (T_FLOAT*)p;
        uv[0] = mesh->mTextureCoords[0][v].x;
        uv[1] = mesh->mTextureCoords[0][v].y;
        p += V_ATTRSIZE_UV;
      }
      if (ret->vertex_format_ & V_ATTR_UV2)
      {
        T_FLOAT* uv2 = (T_FLOAT*)p;
        uv2[0] = mesh->mTextureCoords[1][v].x;
        uv2[1] = mesh->mTextureCoords[1][v].y;
        p += V_ATTRSIZE_UV2;
      }
      if (ret->vertex_format_ & V_ATTR_UV3)
      {
        T_FLOAT* uv3 = (T_FLOAT*)p;
        uv3[0] = mesh->mTextureCoords[2][v].x;
        uv3[1] = mesh->mTextureCoords[2][v].y;
        p += V_ATTRSIZE_UV3;
      }
      if (ret->vertex_format_ & V_ATTR_UV4)
      {
        T_FLOAT* uv4 = (T_FLOAT*)p;
        uv4[0] = mesh->mTextureCoords[3][v].x;
        uv4[1] = mesh->mTextureCoords[3][v].y;
        p += V_ATTRSIZE_UV4;
      }
      if (ret->vertex_format_ & V_ATTR_TANGENT)
      {
        //TODO:
        T_FLOAT* tangent = (T_FLOAT*)p;
        tangent[0] = mesh->mTangents[v].x;
        tangent[1] = mesh->mTangents[v].y;
        tangent[2] = mesh->mTangents[v].z;
        tangent[3] = 0.0f;
        p += V_ATTRSIZE_TANGENT;
      }
      if (ret->vertex_format_ & V_ATTR_COLOR)
      {
        T_UINT32* color = (T_UINT32*)p;
        color[0] =
          (((T_UINT8)(mesh->mColors[0][v].a * 0xff) & 0xff) << 24) |
          (((T_UINT8)(mesh->mColors[0][v].r * 0xff) & 0xff) << 16) |
          (((T_UINT8)(mesh->mColors[0][v].g * 0xff) & 0xff) << 8) |
          (((T_UINT8)(mesh->mColors[0][v].b * 0xff) & 0xff) << 0);
        p += V_ATTRSIZE_COLOR;
      }
    }
    //
    for (T_UINT32 f = 0; f < mesh->mNumFaces; ++f)
    {
      for (T_UINT32 fi = 0; fi < mesh->mFaces[f].mNumIndices; ++fi)
      {
        ret->indices_[ii] = mesh->mFaces[f].mIndices[fi];
        ++ii;
      }
    }
  }

  ret->bounds_.center.x = (min.x + max.y) * 0.5f;
  ret->bounds_.center.y = (min.y + max.y) * 0.5f;
  ret->bounds_.center.z = (min.z + max.z) * 0.5f;

  ret->bounds_.extents.x = (max.x - min.x) * 0.5f;
  ret->bounds_.extents.y = (max.y - min.y) * 0.5f;
  ret->bounds_.extents.z = (max.z - min.z) * 0.5f;

  ret->material_count_ = ret->submesh_count_;
  ret->materials_ = new StaticModelMaterialData[ret->material_count_]();
  for (T_INT32 i = 0; i < ret->material_count_; ++i)
  {
    ImportMaterial(info, scene->mMaterials[i], &ret->materials_[i]);
  }

  return ret;
}

} // namespace Assimp

} // namespace ModelImporter