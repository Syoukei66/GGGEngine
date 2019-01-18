#include "StaticModelConverter.h"

#include <Converter/AssetConverterContext.h>
#include <Entity/File/Model/AssimpImportUtil.h>

// =================================================================
// Methods from AssetConverter
// =================================================================
void ImportMesh(const AssetMetaData* model_asset_info, const aiScene* scene, AssetConverterContext* context, StaticMeshData* dest)
{
  if (scene->mNumMeshes == 0)
  {
    Log::Warn("メッシュの数が０個でした");
    return;
  }

  using namespace Vertex;

  SharedRef<rcDynamicMesh> ret = rcDynamicMesh::Create();

  T_UINT32 vertex_count = 0;
  // 頂点データの作成
  for (T_UINT32 m = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];
    GG_ASSERT(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE, "ポリゴンが三角形ではありません");
    vertex_count += mesh->mNumVertices;
  }
  ret->CreateVertices(vertex_count, V_FORMAT_PNUT);

  T_UINT32 index_offset = 0;
  bool need_recalculate_normals = false;
  bool need_recalculate_tangents = false;
  // インデックスデータの作成
  // （頂点サイズが分からないとインデックスのサイズが決まらないため）
  for (T_UINT32 m = 0, vi = 0; m < scene->mNumMeshes; ++m)
  {
    const aiMesh* mesh = scene->mMeshes[m];
    ret->AddIndices(mesh->mNumFaces * 3);

    // 頂点データの作成
    for (T_UINT32 v = 0; v < mesh->mNumVertices; ++v, ++vi)
    {
      // Vertex
      GG_ASSERT(mesh->HasPositions(), "位置情報が含まれていないメッシュがあります");

      const aiVector3D& vec = mesh->mVertices[v];
      ret->SetVertex(vi, TVec3f(vec.x, vec.y, vec.z));

      // Normal
      if (mesh->HasNormals())
      {
        const aiVector3D& normal = mesh->mNormals[v];
        ret->SetNormal(vi, TVec3f(normal.x, normal.y, normal.z));
      }
      else
      {
        need_recalculate_normals = true;
      }
      // Uv
      if (mesh->HasTextureCoords(0))
      {
        const aiVector3D& uv = mesh->mTextureCoords[0][v];
        ret->SetUv(vi, TVec2f(uv.x, uv.y));
      }
      else
      {
        ret->SetUv(vi, TVec2f(vec.x, vec.y));
      }
      // Tangent
      if (mesh->HasTangentsAndBitangents())
      {
        const aiVector3D& tangent = mesh->mTangents[v];
        ret->SetTangent(vi, TVec4f(tangent.x, tangent.y, tangent.z, 1.0f));
      }
      else
      {
        need_recalculate_tangents = true;
      }
    }

    // インデックスデータの作成
    for (T_UINT32 f = 0, ii = 0; f < mesh->mNumFaces; ++f)
    {
      for (T_UINT32 i = 0; i < 3; ++i, ++ii)
      {
        ret->SetIndex(m, ii, index_offset + mesh->mFaces[f].mIndices[i]);
      }
    }

    index_offset += vertex_count;
  }
  if (need_recalculate_normals)
  {
    ret->RecalculateNormals();
  }
  if (need_recalculate_tangents)
  {
    ret->RecalculateTangents();
  }
  ret->RecalculateBounds();

  ret->ConvertToData(dest);
}

IAssetDataContainer* StaticModelAssetConverter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const
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

  //Mesh
  ImportMesh(meta, scene, context, &data->mesh_);

  //Material
  std::vector<SharedRef<AssetEntity>> material_entities;
  for (T_UINT32 i = 0; i < scene->mNumMaterials; ++i)
  {
    aiMaterial* mat = scene->mMaterials[i];
    const SharedRef<AssetEntity>& material_asset_entity = context->AddEntity(ImportMaterial(meta, mat, this, context));
    material_entities.push_back(material_asset_entity);
  }

  for (T_UINT32 i = 0; i < scene->mNumMeshes; ++i)
  {
    aiMesh* mesh = scene->mMeshes[i];
    data->material_unique_ids_.emplace_back(material_entities[mesh->mMaterialIndex]->GetMetaData()->GetUniqueID());
  }

  // サブアセットをロードし、ConverterSettingに登録を行う
  meta->GetConverterSetting()->ClearSubAssets();
  for (const SharedRef<AssetEntity>& sub_asset : material_entities)
  {
    sub_asset->Load(context);
    meta->GetConverterSetting()->AddSubAsset(sub_asset->GetMetaData()->GetUniqueID());
  }

  aiReleaseImport(scene);

  return new AssetDataContainer<StaticModelData>(data, this);
}
