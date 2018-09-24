#include "ModelAssetImporter.h"
#include "Extensions.h"

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "../Core/GraphicsConstants.h"
#include "../Core/ModelData.h"
#include "../Core/MaterialData.h"
#include "../Core/MeshData.h"

#include "AssetConverterContext.h"
#include "Director.h"

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
static TVec2f ToTVec2f(const aiVector2D& vec)
{
  TVec2f ret;
  ret.x = vec.x;
  ret.y = vec.y;
  return ret;
}

static TVec3f ToTVec3f(const aiVector3D& vec)
{
  TVec3f ret;
  ret.x = vec.x;
  ret.y = vec.y;
  ret.z = vec.z;
  return ret;
}

static TColor ToTColor(const aiColor4D& col)
{
  TColor ret;
  ret.r = col.r;
  ret.g = col.g;
  ret.b = col.b;
  ret.a = col.a;
  return ret;
}

static void ImportMesh(const aiScene* scene, MeshData* dest)
{

  using namespace Graphics;

  dest->submesh_count_ = scene->mNumMeshes;
  dest->submesh_index_counts_ = new T_UINT32[dest->submesh_count_]();
  //
  for (T_UINT32 m = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];
    dest->vertex_count_ += mesh->mNumVertices;
    dest->polygon_count_ += mesh->mNumFaces;
    for (T_UINT32 f = 0, ii = 0; f < mesh->mNumFaces; ++f)
    {
      dest->index_count_ += mesh->mFaces[f].mNumIndices;
      dest->submesh_index_counts_[m] += mesh->mFaces[f].mNumIndices;
    }

    if (!(dest->vertex_format_ & V_ATTR_POSITION) && mesh->HasPositions())
    {
      dest->vertex_format_ |= V_ATTR_POSITION;
      dest->vertex_size_ += V_ATTRSIZE_POSITION;
    }

    if (!(dest->vertex_format_ & V_ATTR_NORMAL) && mesh->HasNormals())
    {
      dest->vertex_format_ |= V_ATTR_NORMAL;
      dest->vertex_size_ += V_ATTRSIZE_NORMAL;
    }

    if (!(dest->vertex_format_ & V_ATTR_UV) && mesh->HasTextureCoords(0))
    {
      dest->vertex_format_ |= V_ATTR_UV;
      dest->vertex_size_ += V_ATTRSIZE_UV;
    }

    if (!(dest->vertex_format_ & V_ATTR_UV2) && mesh->HasTextureCoords(1))
    {
      dest->vertex_format_ |= V_ATTR_UV2;
      dest->vertex_size_ += V_ATTRSIZE_UV2;
    }

    if (!(dest->vertex_format_ & V_ATTR_UV3) && mesh->HasTextureCoords(2))
    {
      dest->vertex_format_ |= V_ATTR_UV3;
      dest->vertex_size_ += V_ATTRSIZE_UV3;
    }

    if (!(dest->vertex_format_ & V_ATTR_UV4) && mesh->HasTextureCoords(3))
    {
      dest->vertex_format_ |= V_ATTR_UV4;
      dest->vertex_size_ += V_ATTRSIZE_UV4;
    }

    if (!(dest->vertex_format_ & V_ATTR_TANGENT) && mesh->HasTangentsAndBitangents())
    {
      dest->vertex_format_ |= V_ATTR_TANGENT;
      dest->vertex_size_ += V_ATTRSIZE_TANGENT;
    }

    if (!(dest->vertex_format_ & V_ATTR_COLOR) && mesh->HasVertexColors(0))
    {
      dest->vertex_format_ |= V_ATTR_COLOR;
      dest->vertex_size_ += V_ATTRSIZE_COLOR;
    }
  }

  TVec3f min = { 0.0f, 0.0f, 0.0f };
  TVec3f max = { 0.0f, 0.0f, 0.0f };

  //
  dest->data_ = new unsigned char[dest->vertex_count_ * dest->vertex_size_]();
  dest->indices_ = new T_UINT32[dest->index_count_]();
  unsigned char* p = dest->data_;
  for (T_UINT32 m = 0, ii = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];

    //
    for (T_UINT32 v = 0; v < mesh->mNumVertices; ++v)
    {
      //mesh
      if (dest->vertex_format_ & V_ATTR_POSITION)
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
      if (dest->vertex_format_ & V_ATTR_NORMAL)
      {
        T_FLOAT* normal = (T_FLOAT*)p;
        normal[0] = mesh->mNormals[v].x;
        normal[1] = mesh->mNormals[v].y;
        normal[2] = mesh->mNormals[v].z;
        p += V_ATTRSIZE_NORMAL;
      }
      if (dest->vertex_format_ & V_ATTR_UV)
      {
        T_FLOAT* uv = (T_FLOAT*)p;
        uv[0] = mesh->mTextureCoords[0][v].x;
        uv[1] = mesh->mTextureCoords[0][v].y;
        p += V_ATTRSIZE_UV;
      }
      if (dest->vertex_format_ & V_ATTR_UV2)
      {
        T_FLOAT* uv2 = (T_FLOAT*)p;
        uv2[0] = mesh->mTextureCoords[1][v].x;
        uv2[1] = mesh->mTextureCoords[1][v].y;
        p += V_ATTRSIZE_UV2;
      }
      if (dest->vertex_format_ & V_ATTR_UV3)
      {
        T_FLOAT* uv3 = (T_FLOAT*)p;
        uv3[0] = mesh->mTextureCoords[2][v].x;
        uv3[1] = mesh->mTextureCoords[2][v].y;
        p += V_ATTRSIZE_UV3;
      }
      if (dest->vertex_format_ & V_ATTR_UV4)
      {
        T_FLOAT* uv4 = (T_FLOAT*)p;
        uv4[0] = mesh->mTextureCoords[3][v].x;
        uv4[1] = mesh->mTextureCoords[3][v].y;
        p += V_ATTRSIZE_UV4;
      }
      if (dest->vertex_format_ & V_ATTR_TANGENT)
      {
        //TODO:
        T_FLOAT* tangent = (T_FLOAT*)p;
        tangent[0] = mesh->mTangents[v].x;
        tangent[1] = mesh->mTangents[v].y;
        tangent[2] = mesh->mTangents[v].z;
        tangent[3] = 0.0f;
        p += V_ATTRSIZE_TANGENT;
      }
      if (dest->vertex_format_ & V_ATTR_COLOR)
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
        dest->indices_[ii] = mesh->mFaces[f].mIndices[fi];
        ++ii;
      }
    }
  }

  dest->bounds_.center.x = (min.x + max.y) * 0.5f;
  dest->bounds_.center.y = (min.y + max.y) * 0.5f;
  dest->bounds_.center.z = (min.z + max.z) * 0.5f;

  dest->bounds_.extents.x = (max.x - min.x) * 0.5f;
  dest->bounds_.extents.y = (max.y - min.y) * 0.5f;
  dest->bounds_.extents.z = (max.z - min.z) * 0.5f;
}

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
      const std::string full_path = info->GetDirectoryPath() + path.C_Str();
      ret = Director::GetInstance().GetUniqueId(full_path);
    }
  }
  return ret;
}

static void ImportMaterial(AssetInfo* info, const aiMaterial* material, MaterialData* dest)
{
  //Colors
  aiColor4D color;
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
  {
    dest->color_ = ToTColor(color);
  }
  dest->main_tex_unique_id_ = ImportTexture(info, material, aiTextureType_DIFFUSE);
  dest->tiling_ = TVec2f(1.0f, 1.0f);
  dest->tiling_offset_ = TVec2f(0.0f, 0.0f);
}

ModelAssetEntity* ModelAssetImporter::ImportProcess(AssetInfo* info, AssetConverterContext* context)
{  
  //一部のファイルでメモリリークが発生
  Assimp::Importer importer = Assimp::Importer();
  const aiScene* scene = importer.ReadFile(
    info->GetFullPath(),
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

  //full_path + .mesh のファイルがあるかどうか検出
  // あれば.meshファイルがprotectedになっているか確認
  //  protectedであれば何もしない。ログにmesh is protectedとでも表示する
  //  protectedでなければSceneを基にデータを更新、AssetInfoに更新を指示する
  // なければsceneを基に新規作成し、AddAssetInfo
  std::string mesh_path = info->GetFullPath() + "." + Extensions::MESH;
  MeshData mesh;
  ImportMesh(scene, &mesh);
  mesh.Deserealize(mesh_path);
  AssetInfo* mesh_info = context->Reserve(info->GetDirectoryPath(), mesh_path, Extensions::MESH);

  data->mesh_unique_id_ = mesh_info->GetUniqueId();
  data->submesh_count_ = mesh.submesh_count_;


  T_UINT32 material_count = scene->mNumMaterials;
  for (T_UINT32 i = 0; i < material_count; ++i)
  {
    aiMaterial* mat = scene->mMaterials[i];
    std::string material_path = info->GetDirectoryPath() + scene->m + "." + Extensions::MATERIAL;
    MaterialData material;
    ImportMaterial(info, mat, &material);
    material.Deserealize(material_path);
    AssetInfo* material_info = context->Reserve(info->GetDirectoryPath(), material_path, Extensions::MATERIAL);
  }

  data->material_count_ = material_count;

  return;
}
