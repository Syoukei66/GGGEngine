#include "CharacterModelAssetImporter.h"

#include <Constants/Extensions.h>
#include <Converter/AssetConverterContext.h>
#include <Util/FileUtil.h>

#include <Director.h>

#include <Entity/File/Model/DynamicMesh/ModelDynamicMeshAssetEntity.h>

#include <Entity/File/Model/AssimpImportUtil.h>

// =================================================================
// Constructor / Destructor
// =================================================================
CharacterModelAssetImporter::CharacterModelAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================
SharedRef<ModelDynamicMeshAssetEntity> ImportMesh(const AssetMetaData* model_asset_info, const aiScene* scene, const aiMesh* mesh, AssetConverterContext* context)
{
  SharedRef<rcDynamicMesh> ret = rcDynamicMesh::Create();

  using namespace Vertex;

  T_UINT32 format = 0;
  format |= mesh->HasPositions() ? V_ATTR_POSITION : 0;
  format |= mesh->HasNormals() ? V_ATTR_NORMAL : 0;
  format |= mesh->HasTextureCoords(0) ? V_ATTR_UV : 0;
  format |= mesh->HasTextureCoords(1) ? V_ATTR_UV2 : 0;
  format |= mesh->HasTextureCoords(2) ? V_ATTR_UV3 : 0;
  format |= mesh->HasTextureCoords(3) ? V_ATTR_UV4 : 0;
  format |= mesh->HasTangentsAndBitangents() ? V_ATTR_TANGENT : 0;
  format |= mesh->HasVertexColors(0) ? V_ATTR_COLOR : 0;

  ret->CreateVertices(mesh->mNumVertices, format);

  //
  for (T_UINT32 v = 0; v < mesh->mNumVertices; ++v)
  {
    // Vertex
    if (format & V_ATTR_POSITION)
    {
      const aiVector3D& vec = mesh->mVertices[v];
      ret->SetVertex(v, TVec3f(vec.x, vec.y, vec.z));
    }
    // Normal
    if (format & V_ATTR_NORMAL)
    {
      const aiVector3D& vec = mesh->mNormals[v];
      ret->SetNormal(v, TVec3f(vec.x, vec.y, vec.z));
    }
    // Uv
    if (format & V_ATTR_UV)
    {
      const aiVector3D& vec = mesh->mTextureCoords[0][v];
      ret->SetUv(v, TVec2f(vec.x, vec.y));
    }
    // Uv2
    if (format & V_ATTR_UV2)
    {
      const aiVector3D& vec = mesh->mTextureCoords[1][v];
      ret->SetUv2(v, TVec2f(vec.x, vec.y));
    }
    // Uv3
    if (format & V_ATTR_UV3)
    {
      const aiVector3D& vec = mesh->mTextureCoords[2][v];
      ret->SetUv3(v, TVec2f(vec.x, vec.y));
    }
    // Uv4
    if (format & V_ATTR_UV4)
    {
      const aiVector3D& vec = mesh->mTextureCoords[3][v];
      ret->SetUv4(v, TVec2f(vec.x, vec.y));
    }
    // Tangent
    if (format & V_ATTR_TANGENT)
    {
      const aiVector3D& vec = mesh->mTangents[v];
      ret->SetTangent(v, TVec4f(vec.x, vec.y, vec.z, 1.0f));
    }
    // Color
    if (format & V_ATTR_COLOR)
    {
      const aiColor4D& col = mesh->mColors[0][v];
      ret->SetColor(v, TColor(col.r, col.g, col.b, col.a));
    }
  }

  //
  ret->AddIndices(mesh->mNumFaces * 3);
  for (T_UINT32 f = 0, ii = 0; f < mesh->mNumFaces; ++f)
  {
    GG_ASSERT(mesh->mFaces[f].mNumIndices == 3, "ポリゴンが三角形ではありません");
    for (T_UINT32 fi = 0; fi < mesh->mFaces[f].mNumIndices; ++fi, ++ii)
    {
      ret->SetIndex(ii, mesh->mFaces[f].mIndices[fi]);
    }
  }

  ret->RecalculateBounds();

  AssetMetaData* mesh_asset_info = AssetMetaData::Create(
    URI(model_asset_info->GetURI().GetDirectoryPath(), model_asset_info->GetURI().GetPrefix(), Extensions::DYNAMIC_MESH),
    model_asset_info->GetUniqueID(),
    context
  );

  DynamicMeshData* data = new DynamicMeshData();

  ret->ConvertToData(data);

  return ModelDynamicMeshAssetEntity::Create(mesh_asset_info, data);
}

void ImportNode(const aiNode* node, CharacterNodeData* dest)
{ 
  aiVector3D position;
  aiVector3D scaling;
  aiVector3D rotation;
  node->mTransformation.Decompose(scaling, rotation, position);
  dest->position_ = TVec3f(position.x, position.y, position.z);
  dest->scale_ = TVec3f(scaling.x, scaling.y, scaling.z);
  dest->rotation_ = TVec3f(rotation.x, rotation.y, rotation.z);
  for (T_UINT32 i = 0; i < node->mNumMeshes; ++i)
  {
    dest->mesh_indices_.emplace_back(node->mMeshes[i]);
  }
  dest->children_.resize(node->mNumChildren);
  for (T_UINT32 i = 0; i < node->mNumChildren; ++i)
  {
    ImportNode(node->mChildren[i], &dest->children_[i]);
  }
}

SharedRef<CharacterModelAssetEntity> CharacterModelAssetImporter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context)
{
  using namespace Assimp;
  // 一部のファイルでメモリリークが発生
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

  CharacterModelData* data = new CharacterModelData();

  std::vector<SharedRef<AssetEntity>> referenced_assets = std::vector<SharedRef<AssetEntity>>();

  // Mesh
  for (T_UINT32 i = 0; i < scene->mNumMeshes; ++i)
  {
    aiMesh* mesh = scene->mMeshes[i];
    const SharedRef<AssetEntity>& mesh_asset_entity = context->AddEntity(ImportMesh(meta, scene, mesh, context));
    referenced_assets.push_back(mesh_asset_entity);
    data->mesh_unique_ids_.emplace_back(mesh_asset_entity->GetMetaData()->GetUniqueID());
    data->mesh_material_indices_.emplace_back(mesh->mMaterialIndex);
  }

  // Material
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

  // Node
  ImportNode(scene->mRootNode, &data->root_node_);

  const SharedRef<CharacterModelAssetEntity>& entity = CharacterModelAssetEntity::Create(meta, data);
  for (const SharedRef<AssetEntity>& referenced : referenced_assets)
  {
    entity->AddReferencedEntity(referenced);
  }

  aiReleaseImport(scene);

  return entity;
}
