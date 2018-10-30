#include "ModelAssetImporter.h"

#include <assimp/Importer.hpp>
#include <Assimp/cimport.h>
#include <assimp/postprocess.h>

#include <Constants/Extensions.h>
#include <Converter/AssetConverterContext.h>
#include <Util/FileUtil.h>

#include <Converter/AssetConverterContext.h>
#include "Director.h"
#include <Util/FileUtil.h>

#include <Entity/File/Model/Mesh/ModelMeshAssetEntity.h>
#include <Entity/File/Model/Material/ModelMaterialAssetEntity.h>
#include <Entity/File/Texture/TextureAssetEntity.h>

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

  using namespace Vertex;

  T_UINT32 index_count = 0;

  ret->submesh_count_ = scene->mNumMeshes;
  ret->submesh_index_counts_.resize(ret->submesh_count_);
  ret->submesh_polygon_counts_.resize(ret->submesh_count_);
  //
  for (T_UINT32 m = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];
    ret->vertex_count_ += mesh->mNumVertices;
    ret->submesh_polygon_counts_[m] = mesh->mNumFaces;
    GG_ASSERT(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE, "ポリゴンが三角形ではありません");
    ret->submesh_index_counts_[m] = 3 * mesh->mNumFaces;
    index_count += ret->submesh_index_counts_[m];

    if (mesh->HasPositions()) ret->vertex_format_ |= V_ATTR_POSITION;
    if (mesh->HasNormals()) ret->vertex_format_ |= V_ATTR_NORMAL;
    if (mesh->HasTextureCoords(0)) ret->vertex_format_ |= V_ATTR_UV;
    if (mesh->HasTextureCoords(1)) ret->vertex_format_ |= V_ATTR_UV2;
    if (mesh->HasTextureCoords(2)) ret->vertex_format_ |= V_ATTR_UV3;
    if (mesh->HasTextureCoords(3)) ret->vertex_format_ |= V_ATTR_UV4;
    if (mesh->HasTangentsAndBitangents()) ret->vertex_format_ |= V_ATTR_TANGENT;
    if (mesh->HasVertexColors(0)) ret->vertex_format_ |= V_ATTR_COLOR;
  }

  ret->vertex_size_ = CalcVertexSize(ret->vertex_format_);

  TVec3f min = { 0.0f, 0.0f, 0.0f };
  TVec3f max = { 0.0f, 0.0f, 0.0f };

  //
  ret->data_.resize(ret->vertex_count_ * ret->vertex_size_);
  ret->indices_.resize(index_count);
  T_UINT32 index_offset = 0;
  unsigned char* p = &ret->data_[0];
  for (T_UINT32 m = 0, ii = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];

    //
    for (T_UINT32 v = 0; v < mesh->mNumVertices; ++v)
    {
      //mesh
      if (ret->vertex_format_ & V_ATTR_POSITION)
      {
        const aiVector3D& vec = mesh->mVertices[v];
        SetVertexPosition(TVec3f(vec.x, vec.y, vec.z), &p);

        min.x = std::min(min.x, vec.x);
        min.y = std::min(min.y, vec.y);
        min.z = std::min(min.z, vec.z);

        max.x = std::max(max.x, vec.x);
        max.y = std::max(max.y, vec.y);
        max.z = std::max(max.z, vec.z);
      }
      if (ret->vertex_format_ & V_ATTR_NORMAL)
      {
        const aiVector3D& vec = mesh->mNormals[v];
        SetVertexNormal(TVec3f(vec.x, vec.y, vec.z), &p);
      }
      if (ret->vertex_format_ & V_ATTR_UV)
      {
        const aiVector3D& vec = mesh->mTextureCoords[0][v];
        SetVertexUv(TVec2f(vec.x, vec.y), &p);
      }
      if (ret->vertex_format_ & V_ATTR_UV2)
      {
        const aiVector3D& vec = mesh->mTextureCoords[1][v];
        SetVertexUv2(TVec2f(vec.x, vec.y), &p);
      }
      if (ret->vertex_format_ & V_ATTR_UV3)
      {
        const aiVector3D& vec = mesh->mTextureCoords[2][v];
        SetVertexUv3(TVec2f(vec.x, vec.y), &p);
      }
      if (ret->vertex_format_ & V_ATTR_UV4)
      {
        const aiVector3D& vec = mesh->mTextureCoords[3][v];
        SetVertexUv4(TVec2f(vec.x, vec.y), &p);
      }
      if (ret->vertex_format_ & V_ATTR_TANGENT)
      {
        const aiVector3D& vec = mesh->mTangents[v];
        SetVertexTangent(TVec4f(vec.x, vec.y, vec.z, 1.0f), &p);
      }
      if (ret->vertex_format_ & V_ATTR_COLOR)
      {
        const aiColor4D& col = mesh->mColors[0][v];
        SetVertexColor(TColor(col.r, col.g, col.b, col.a), &p);
      }
    }
    //
    for (T_UINT32 f = 0; f < mesh->mNumFaces; ++f)
    {
      GG_ASSERT(mesh->mFaces[f].mNumIndices == 3, "ポリゴンが三角形ではありません");
      for (T_UINT32 fi = 0; fi < mesh->mFaces[f].mNumIndices; ++fi)
      {
        ret->indices_[ii] = index_offset + mesh->mFaces[f].mIndices[fi];
        ++ii;
      }
    }
    index_offset += mesh->mNumVertices;
  }

  ret->bounds_.center.x = (min.x + max.y) * 0.5f;
  ret->bounds_.center.y = (min.y + max.y) * 0.5f;
  ret->bounds_.center.z = (min.z + max.z) * 0.5f;

  ret->bounds_.extents.x = (max.x - min.x) * 0.5f;
  ret->bounds_.extents.y = (max.y - min.y) * 0.5f;
  ret->bounds_.extents.z = (max.z - min.z) * 0.5f;

  return ret;
}

static T_UINT32 ImportTexture(AssetInfo* info, const aiMaterial* material, aiTextureType type, AssetConverterContext* context)
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
      return context->ImportImmediately<TextureAssetEntity>(URI(info->GetURI().GetDirectoryPath(), path.C_Str()))->GetAssetInfo()->GetUniqueID();
    }
  }
  return 0;
}

static T_UINT32 ImportShader(AssetInfo* info, const aiMaterial* material, AssetConverterContext* context)
{
  T_INT32 mode;
  if (AI_SUCCESS == material->Get(AI_MATKEY_SHADING_MODEL, mode))
  {
    return DefaultUniqueID::DEFAULT_UID_BEGIN + mode;
  }
  return DefaultUniqueID::SHADER_GOURAUD;
}

static MaterialData* ImportMaterial(AssetInfo* info, const aiMaterial* material, AssetConverterContext* context)
{
  MaterialData* dest = new MaterialData();

  //Colors
  aiColor4D color;
  if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
  {
    dest->color_ = ToTColor(color);
  }
  dest->main_tex_unique_id_ = ImportTexture(info, material, aiTextureType_DIFFUSE, context);
  dest->tiling_ = TVec2f(1.0f, 1.0f);
  dest->tiling_offset_ = TVec2f(0.0f, 0.0f);
  //TODO:プロパティのインポート処理
  dest->shader_unique_id_ = ImportShader(info, material, context);

  return dest;
}

ModelAssetEntity* ModelAssetImporter::ImportProcess(AssetInfo* info, AssetConverterContext* context)
{  
  using namespace Assimp;
  //一部のファイルでメモリリークが発生
  Assimp::Importer importer;

  unsigned int ppsteps = aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
    aiProcess_JoinIdenticalVertices | // join identical vertices/ optimize indexing
    aiProcess_ValidateDataStructure | // perform a full validation of the loader's output
    aiProcess_ImproveCacheLocality | // improve the cache locality of the output vertices
    aiProcess_RemoveRedundantMaterials | // remove redundant materials
    aiProcess_FindDegenerates | // remove degenerated polygons from the import
    aiProcess_FindInvalidData | // detect invalid model data, such as invalid normal vectors
    aiProcess_GenUVCoords | // convert spherical, cylindrical, box and planar mapping to proper UVs
    aiProcess_TransformUVCoords | // preprocess UV transformations (scaling, translation ...)
    aiProcess_FindInstances | // search for instanced meshes and remove them by references to one master
    aiProcess_LimitBoneWeights | // limit bone weights to 4 per vertex
    aiProcess_OptimizeMeshes | // join small meshes, if possible;
    aiProcess_SplitByBoneCount | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
    0;
  float g_smoothAngle = 80.f;
  bool nopointslines = true;

  aiPropertyStore* props = aiCreatePropertyStore();
  aiSetImportPropertyInteger(props, AI_CONFIG_IMPORT_TER_MAKE_UVS, 1);
  aiSetImportPropertyFloat(props, AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, g_smoothAngle);
  aiSetImportPropertyInteger(props, AI_CONFIG_PP_SBP_REMOVE, nopointslines ? aiPrimitiveType_LINE | aiPrimitiveType_POINT : 0);

  aiSetImportPropertyInteger(props, AI_CONFIG_GLOB_MEASURE_TIME, 1);
  aiSetImportPropertyInteger(props, AI_CONFIG_PP_PTV_NORMALIZE, 1);

  const aiScene* scene = aiImportFileExWithProperties(
    info->GetInputPath().c_str(),
    ppsteps | /* configurable pp steps */
    aiProcess_GenSmoothNormals | // generate smooth normal vectors if not existing
    aiProcess_SplitLargeMeshes | // split large, unrenderable meshes into submeshes
    aiProcess_Triangulate | // triangulate polygons with more than 3 edges
    aiProcess_PreTransformVertices |
    aiProcess_ConvertToLeftHanded | // convert everything to D3D left handed space
    aiProcess_SortByPType | // make 'clean' meshes which consist of a single typ of primitives
    0,
    NULL,
    props);

  aiReleasePropertyStore(props);

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

  return new ModelAssetEntity(info, data, scene);
}
