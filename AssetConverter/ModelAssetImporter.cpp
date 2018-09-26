#include "ModelAssetImporter.h"
#include "../Core/GraphicsConstants.h"

#include "Extensions.h"
#include "AssetConverterContext.h"
#include "FileUtil.h"

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

#include "AssetConverterContext.h"
#include "Director.h"
#include "FileUtil.h"

#include "ModelMeshAssetEntity.h"
#include "ModelMaterialAssetEntity.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelAssetImporter::ModelAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================

TVec2f ToTVec2f(const aiVector2D & vec)
{
  TVec2f ret;
  ret.x = vec.x;
  ret.y = vec.y;
  return ret;
}

TVec3f ToTVec3f(const aiVector3D & vec)
{
  TVec3f ret;
  ret.x = vec.x;
  ret.y = vec.y;
  ret.z = vec.z;
  return ret;
}

TColor ToTColor(const aiColor4D & col)
{
  TColor ret;
  ret.r = col.r;
  ret.g = col.g;
  ret.b = col.b;
  ret.a = col.a;
  return ret;
}

static MeshData* ImportMesh(const aiScene* scene)
{
  MeshData* ret = new MeshData();

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

  return ret;
}

static AssetInfo* ImportTexture(AssetInfo* info, const aiMaterial* material, aiTextureType type, AssetConverterContext* context)
{
  aiString path;
  aiTextureMapping mapping;
  T_UINT32 uv_index;
  T_FLOAT blend;
  aiTextureOp op;
  aiTextureMapMode map_mode;
  T_UINT32 flags;

  for (T_UINT8 i = 0; i < 8; ++i)
  {
    if (AI_SUCCESS == aiGetMaterialTexture(material, type, i, &path, &mapping, &uv_index, &blend, &op, &map_mode, &flags))
    {
      return context->Reserve(URI(info->GetURI().GetDirectoryPath(), path.C_Str()));
    }
  }
  return nullptr;
}

static  MaterialData* ImportMaterial(AssetInfo* info, const aiMaterial* material, AssetConverterContext* context)
{
  MaterialData* dest = new MaterialData();

  //Colors
  aiColor4D color;
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
  {
    dest->color_ = ToTColor(color);
  }
  dest->main_tex_unique_id_ = ImportTexture(info, material, aiTextureType_DIFFUSE, context)->GetUniqueID();
  dest->tiling_ = TVec2f(1.0f, 1.0f);
  dest->tiling_offset_ = TVec2f(0.0f, 0.0f);
  //TODO:プロパティのインポート処理

  return dest;
}

ModelAssetEntity* ModelAssetImporter::ImportProcess(AssetInfo* info, AssetConverterContext* context)
{  
  //一部のファイルでメモリリークが発生
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(
    info->GetURI().GetFullPath(),
    aiProcess_GenNormals |
    aiProcess_CalcTangentSpace |
    aiProcess_Triangulate |
    aiProcess_JoinIdenticalVertices |
    aiProcess_SortByPType |
    aiProcess_MakeLeftHanded |
    aiProcess_LimitBoneWeights |
    aiProcess_ImproveCacheLocality |
    aiProcess_SplitByBoneCount |
    aiProcess_PreTransformVertices
  );

  ModelData* data = new ModelData();

  //Mesh
  MeshData* mesh_data = ImportMesh(scene);
  AssetInfo* mesh_asset_info = AssetInfo::Create(URI(info->GetURI().GetDirectoryPath(), info->GetURI().GetPrefix(), Extensions::MESH), context);
  context->AddEntity(new ModelMeshAssetEntity(mesh_asset_info, mesh_data, info->GetUniqueID()));
  data->mesh_unique_id_ = mesh_asset_info->GetUniqueID();

  //Material
  std::vector<AssetInfo*> material_asset_infos;
  for (T_UINT32 i = 0; i < scene->mNumMaterials; ++i)
  {
    aiMaterial* mat = scene->mMaterials[i];
    aiString name;
    if (AI_SUCCESS == aiGetMaterialString(mat, AI_MATKEY_NAME, &name))
    {
      AssetInfo* mat_asset_info = AssetInfo::Create(URI(info->GetURI().GetDirectoryPath(), name.C_Str(), Extensions::MATERIAL), context);
      MaterialData* mat_data = ImportMaterial(mat_asset_info, mat, context);
      context->AddEntity(new ModelMaterialAssetEntity(mat_asset_info, mat_data, info->GetUniqueID()));
      material_asset_infos.push_back(mat_asset_info);
    }
  }

  for (T_UINT32 i = 0; i < scene->mNumMeshes; ++i)
  {
    aiMesh* mesh = scene->mMeshes[i];
    data->material_unique_ids_.push_back(material_asset_infos[mesh->mMaterialIndex]->GetUniqueID());
  }

  return ModelAssetEntity::Create(info, data, scene);
}
