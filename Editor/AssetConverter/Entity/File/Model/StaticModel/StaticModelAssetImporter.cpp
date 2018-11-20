#include "StaticModelAssetImporter.h"

#include <Constants/Extensions.h>
#include <Converter/AssetConverterContext.h>
#include <Util/FileUtil.h>

#include <Director.h>

#include <Entity/File/Model/StaticMesh/ModelStaticMeshAssetEntity.h>

#include <Entity/File/Model/AssimpImportUtil.h>

// =================================================================
// Constructor / Destructor
// =================================================================
StaticModelAssetImporter::StaticModelAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================
SharedRef<ModelStaticMeshAssetEntity> ImportMesh(const AssetMetaData* model_asset_info, const aiScene* scene, AssetConverterContext* context)
{
  if (scene->mNumMeshes == 0)
  {
    Log::Warn("メッシュの数が０個でした");
    return nullptr;
  }

  StaticMeshData* data = new StaticMeshData();

  using namespace Vertex;

  T_UINT32 index_count = 0;

  data->vertex_format_ = V_FORMAT_PNUT;

  data->index_datas_.resize(scene->mNumMeshes);
  data->index_formats_.resize(scene->mNumMeshes);
  data->index_counts_.resize(scene->mNumMeshes);
  data->polygon_counts_.resize(scene->mNumMeshes);
  // 頂点データの作成
  for (T_UINT32 m = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];
    
    GG_ASSERT(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE, "ポリゴンが三角形ではありません");

    data->vertex_count_ += mesh->mNumVertices;
  }
  // インデックスデータの作成
  // （頂点サイズが分からないとインデックスのサイズが決まらないため）
  for (T_UINT32 m = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];

    GG_ASSERT(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE, "ポリゴンが三角形ではありません");

    // 頂点数からインデックスフォーマットを判別する
    Vertex::IndexFormat format = Vertex::IndexFormat::INDEX_FMT_16;
    if (data->vertex_count_ > Limit::T_FIXED_UINT16_MAX)
    {
      format = Vertex::IndexFormat::INDEX_FMT_32;
    }

    data->index_formats_[m] = static_cast<T_UINT8>(format);
    data->index_counts_[m] = 3 * mesh->mNumFaces;
    data->index_datas_[m].resize(data->index_counts_[m] * INDEX_FORMAT_SIZES[data->index_formats_[m]]);
    data->polygon_counts_[m] = mesh->mNumFaces;
  }

  TVec3f min = { 0.0f, 0.0f, 0.0f };
  TVec3f max = { 0.0f, 0.0f, 0.0f };

  //
  data->vertex_data_.resize(data->vertex_count_ * CalcVertexSize(data->vertex_format_));
  T_UINT32 index_offset = 0;
  unsigned char* p = &data->vertex_data_[0];
  for (T_UINT32 m = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];

    //
    for (T_UINT32 v = 0; v < mesh->mNumVertices; ++v)
    {
      // Vertex
      if (data->vertex_format_ & V_ATTR_POSITION)
      {
        GG_ASSERT(mesh->HasPositions(), "位置情報が含まれていないメッシュがあります");

        const aiVector3D& vec = mesh->mVertices[v];
        SetVertexPosition(TVec3f(vec.x, vec.y, vec.z), &p);

        min.x = std::min(min.x, vec.x);
        min.y = std::min(min.y, vec.y);
        min.z = std::min(min.z, vec.z);

        max.x = std::max(max.x, vec.x);
        max.y = std::max(max.y, vec.y);
        max.z = std::max(max.z, vec.z);
      }
      // Normal
      if (data->vertex_format_ & V_ATTR_NORMAL)
      {
        GG_ASSERT(mesh->HasNormals(), "法線情報が含まれていないメッシュがあります");

        const aiVector3D& vec = mesh->mNormals[v];
        SetVertexNormal(TVec3f(vec.x, vec.y, vec.z), &p);
      }
      // Uv
      if (data->vertex_format_ & V_ATTR_UV)
      {
        GG_ASSERT(mesh->HasTextureCoords(0), "UV情報が含まれていないメッシュがあります");

        const aiVector3D& vec = mesh->mTextureCoords[0][v];
        SetVertexUv(TVec2f(vec.x, vec.y), &p);
      }
      // Uv2
      if (data->vertex_format_ & V_ATTR_UV2)
      {
        const aiVector3D& vec = mesh->mTextureCoords[1][v];
        SetVertexUv2(TVec2f(vec.x, vec.y), &p);
      }
      // Uv3
      if (data->vertex_format_ & V_ATTR_UV3)
      {
        const aiVector3D& vec = mesh->mTextureCoords[2][v];
        SetVertexUv3(TVec2f(vec.x, vec.y), &p);
      }
      // Uv4
      if (data->vertex_format_ & V_ATTR_UV4)
      {
        const aiVector3D& vec = mesh->mTextureCoords[3][v];
        SetVertexUv4(TVec2f(vec.x, vec.y), &p);
      }
      // Tangent
      if (data->vertex_format_ & V_ATTR_TANGENT)
      {
        GG_ASSERT(mesh->HasTangentsAndBitangents(), "接空間ベクトル情報が含まれていないメッシュがあります");

        const aiVector3D& vec = mesh->mTangents[v];
        SetVertexTangent(TVec4f(vec.x, vec.y, vec.z, 1.0f), &p);
      }
      // Color
      if (data->vertex_format_ & V_ATTR_COLOR)
      {
        const aiColor4D& col = mesh->mColors[0][v];
        SetVertexColor(TColor(col.r, col.g, col.b, col.a), &p);
      }
    }
    //
    unsigned char* p = &data->index_datas_[m][0];
    for (T_UINT32 f = 0; f < mesh->mNumFaces; ++f)
    {
      GG_ASSERT(mesh->mFaces[f].mNumIndices == 3, "ポリゴンが三角形ではありません");
      for (T_UINT32 fi = 0; fi < mesh->mFaces[f].mNumIndices; ++fi)
      {
        SetIndexIndex(index_offset + mesh->mFaces[f].mIndices[fi], static_cast<IndexFormat>(data->index_formats_[m]), &p);
      }
    }
    index_offset += mesh->mNumVertices;
  }

  data->bounds_.center.x = (min.x + max.y) * 0.5f;
  data->bounds_.center.y = (min.y + max.y) * 0.5f;
  data->bounds_.center.z = (min.z + max.z) * 0.5f;

  data->bounds_.extents.x = (max.x - min.x) * 0.5f;
  data->bounds_.extents.y = (max.y - min.y) * 0.5f;
  data->bounds_.extents.z = (max.z - min.z) * 0.5f;

  AssetMetaData* mesh_asset_info = AssetMetaData::Create(
    URI(model_asset_info->GetURI().GetDirectoryPath(), model_asset_info->GetURI().GetPrefix(), Extensions::STATIC_MESH),
    model_asset_info->GetUniqueID(),
    context
  );

  return ModelStaticMeshAssetEntity::Create(mesh_asset_info, data);
}

SharedRef<StaticModelAssetEntity> StaticModelAssetImporter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context)
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
    meta->GetInputPath().c_str(),
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

  if (!scene)
  {
    aiReleaseImport(scene);
    Log::Warn("シーンの読み込みに失敗しました");
    return nullptr;
  }

  StaticModelData* data = new StaticModelData();

  std::vector<SharedRef<AssetEntity>> referenced_assets = std::vector<SharedRef<AssetEntity>>();

  //Mesh
  const SharedRef<AssetEntity>& mesh_asset_entity = context->AddEntity(ImportMesh(meta, scene, context));
  referenced_assets.push_back(mesh_asset_entity);
  data->mesh_unique_id_ = mesh_asset_entity->GetMetaData()->GetUniqueID();

  //Material
  std::vector<AssetMetaData*> material_asset_infos;
  for (T_UINT32 i = 0; i < scene->mNumMaterials; ++i)
  {
    aiMaterial* mat = scene->mMaterials[i];
    aiString name;
    if (AI_SUCCESS == aiGetMaterialString(mat, AI_MATKEY_NAME, &name))
    {
      AssetMetaData* mat_asset_info = AssetMetaData::Create(URI(meta->GetURI().GetDirectoryPath(), name.C_Str(), Extensions::MATERIAL), meta->GetUniqueID(), context);
      const SharedRef<AssetEntity>& material_asset_entity = context->AddEntity(ImportMaterial(mat_asset_info, mat, context));
      material_asset_infos.push_back(mat_asset_info);
      referenced_assets.push_back(material_asset_entity);
    }
  }

  for (T_UINT32 i = 0; i < scene->mNumMeshes; ++i)
  {
    aiMesh* mesh = scene->mMeshes[i];
    data->material_unique_ids_.push_back(material_asset_infos[mesh->mMaterialIndex]->GetUniqueID());
  }

  const SharedRef<StaticModelAssetEntity>& entity = StaticModelAssetEntity::Create(meta, data);
  for (const SharedRef<AssetEntity>& referenced : referenced_assets)
  {
    entity->AddReferencedEntity(referenced);
  }

  aiReleaseImport(scene);

  return entity;
}
