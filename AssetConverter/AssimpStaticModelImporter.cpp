#include "AssimpStaticModelImporter.h"
#include <assimp\mesh.h>

#include "../Common/GraphicsConstants.h"
#include "../Common/NativeAssert.h"
#include "../Common/Color.h"

#include "AssetManager.h"

#include "AssimpMathImporter.h"
#include "AssimpMaterialSystemImporter.h"

namespace ModelImporter
{

namespace Assimp
{
static void ImportTexture(AssetInfo* info, const aiMaterial* material, aiTextureType type, T_UINT8 index)
{
  aiString path;
  aiTextureMapping mapping;
  T_UINT32 uv_index;
  T_FLOAT blend;
  aiTextureOp op;
  aiTextureMapMode map_mode;
  T_UINT32 flags;
  aiGetMaterialTexture(material, type, index, &path, &mapping, &uv_index, &blend, &op, &map_mode, &flags);

  const std::string full_path = info->directory_path + path.C_Str();

  dest->unique_id_ = AssetManager::GetInstance().GetInfomation(full_path)->meta_data->unique_id;
  dest->uv_index_ = index;
  dest->flags_ = ConvertTextureFlags(flags);
  dest->map_mode_ = ConvertTextureMapMode(map_mode);
  dest->type_ = ConvertTextureType(type);

  info->meta_data->references.emplace(full_path);
}

//=============================================================================
// MaterialData
//=============================================================================
static void ImportMaterial(AssetInfo* info, const aiMaterial* material, StaticModelMaterialData* dest)
{
  using namespace ModelConstants;

  //Colors
  //std::vector<std::pair<ColorType, TColor>> colors = std::vector<std::pair<ColorType, TColor>>();
  aiColor4D color;
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
  {
    dest->tint_ = ToTColor(color);
  //  colors.emplace_back(COL_TYPE_DIFFUSE, ToTColor(color));
  }
  //if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color))
  //{
  //  colors.emplace_back(COL_TYPE_SPECULAR, ToTColor(color));
  //}
  //if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color))
  //{
  //  colors.emplace_back(COL_TYPE_AMBIENT, ToTColor(color));
  //}
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &color))
  {
    dest->emission_ = ToTColor(color);
  //  colors.emplace_back(COL_TYPE_EMISSIVE, ToTColor(color));
  }
  //if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_TRANSPARENT, &color))
  //{
  //  colors.emplace_back(COL_TYPE_TRANSPARENT, ToTColor(color));
  //}

  //Textures
  std::vector<std::pair<aiTextureType, T_UINT8>> textures = std::vector<std::pair<aiTextureType, T_UINT8>>();
  aiString path;
  for (T_UINT32 i = 0; i < AI_TEXTURE_TYPE_MAX; ++i)
  {
    const aiTextureType type = (aiTextureType)i;
    const T_UINT8 texture_count = material->GetTextureCount(type);
    for (T_UINT8 index = 0; index < texture_count; ++index)
    {
      textures.emplace_back(type, index);
    }
  }

  dest->texture_count_ = textures.size();
  if (dest->texture_count_ > 0)
  {
    dest->texture_datas_ = new StaticModelTextureData[dest->texture_count_]();
    for (T_UINT8 i = 0; i < dest->texture_count_; ++i)
    {
      const auto& pair = textures[i];
    }
  }

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
  ret->vertices_ = new T_FLOAT[ret->vertex_count_ * ret->vertex_size_]();
  ret->indices_ = new T_UINT32[ret->index_count_]();
  for (T_UINT32 m = 0, vi = 0, ii = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];

    //
    for (T_UINT32 v = 0; v < mesh->mNumVertices; ++v)
    {
      //mesh
      if (ret->vertex_format_ & V_ATTR_POSITION)
      {
        ret->vertices_[vi + 0] = mesh->mVertices[v].x;
        ret->vertices_[vi + 1] = mesh->mVertices[v].y;
        ret->vertices_[vi + 2] = mesh->mVertices[v].z;

        min.x = std::min(min.x, mesh->mVertices[v].x);
        min.y = std::min(min.y, mesh->mVertices[v].y);
        min.z = std::min(min.z, mesh->mVertices[v].z);

        max.x = std::max(max.x, mesh->mVertices[v].x);
        max.y = std::max(max.y, mesh->mVertices[v].y);
        max.z = std::max(max.z, mesh->mVertices[v].z);

        vi += V_ATTRSIZE_POSITION;
      }
      if (ret->vertex_format_ & V_ATTR_NORMAL)
      {
        ret->vertices_[vi + 0] = mesh->mNormals[v].x;
        ret->vertices_[vi + 1] = mesh->mNormals[v].y;
        ret->vertices_[vi + 2] = mesh->mNormals[v].z;
        vi += V_ATTRSIZE_NORMAL;
      }
      if (ret->vertex_format_ & V_ATTR_UV)
      {
        ret->vertices_[vi + 0] = mesh->mTextureCoords[0][v].x;
        ret->vertices_[vi + 1] = mesh->mTextureCoords[0][v].y;
        vi += V_ATTRSIZE_UV;
      }
      if (ret->vertex_format_ & V_ATTR_UV2)
      {
        ret->vertices_[vi + 0] = mesh->mTextureCoords[1][v].x;
        ret->vertices_[vi + 1] = mesh->mTextureCoords[1][v].y;
        vi += V_ATTRSIZE_UV2;
      }
      if (ret->vertex_format_ & V_ATTR_UV3)
      {
        ret->vertices_[vi + 0] = mesh->mTextureCoords[2][v].x;
        ret->vertices_[vi + 1] = mesh->mTextureCoords[2][v].y;
        vi += V_ATTRSIZE_UV3;
      }
      if (ret->vertex_format_ & V_ATTR_UV4)
      {
        ret->vertices_[vi + 0] = mesh->mTextureCoords[3][v].x;
        ret->vertices_[vi + 1] = mesh->mTextureCoords[3][v].y;
        vi += V_ATTRSIZE_UV4;
      }
      if (ret->vertex_format_ & V_ATTR_TANGENT)
      {
        //TODO:
        ret->vertices_[vi + 0] = mesh->mTangents[v].x;
        ret->vertices_[vi + 1] = mesh->mTangents[v].y;
        ret->vertices_[vi + 2] = mesh->mTangents[v].z;
        ret->vertices_[vi + 3] = 0.0f;
        vi += V_ATTRSIZE_TANGENT;
      }
      if (ret->vertex_format_ & V_ATTR_COLOR)
      {
        ret->vertices_[vi + 0] =
          (((T_UINT8)(mesh->mColors[0][v].a * 0xff) & 0xff) << 24) |
          (((T_UINT8)(mesh->mColors[0][v].r * 0xff) & 0xff) << 16) |
          (((T_UINT8)(mesh->mColors[0][v].g * 0xff) & 0xff) << 8) |
          (((T_UINT8)(mesh->mColors[0][v].b * 0xff) & 0xff) << 0);
        vi += V_ATTRSIZE_COLOR;
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