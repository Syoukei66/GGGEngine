#include "CharacterModelConverter.h"

#include <Converter/AssetConverterContext.h>
#include <Entity/File/Model/AssimpImportUtil.h>

// =================================================================
// Methods from AssetConverter
// =================================================================
void ImportMesh(const AssetMetaData* model_asset_info, const aiScene* scene, const aiMesh* mesh, AssetConverterContext* context, CharacterMeshData* dest)
{
  SharedRef<rcDynamicMesh> ret = rcDynamicMesh::Create();

  using namespace Vertex;

  ret->CreateVertices(mesh->mNumVertices, V_FORMAT_PNUT);

  //
  for (T_UINT32 v = 0; v < mesh->mNumVertices; ++v)
  {
    // Vertex
    const aiVector3D& vec = mesh->mVertices[v];
    ret->SetVertex(v, TVec3f(vec.x, vec.y, vec.z));
    // Normal
    const aiVector3D& normal = mesh->mNormals[v];
    ret->SetNormal(v, TVec3f(normal.x, normal.y, normal.z));
    // Uv
    const aiVector3D& uv = mesh->mTextureCoords[0][v];
    ret->SetUv(v, TVec2f(uv.x, uv.y));
    // Tangent
    const aiVector3D& tangent = mesh->mTangents[v];
    ret->SetTangent(v, TVec4f(tangent.x, tangent.y, tangent.z, 1.0f));
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

  for (T_UINT32 i = 0; i < mesh->mNumAnimMeshes; ++i)
  {
    const aiAnimMesh& anim_mesh = *mesh->mAnimMeshes[i];
  }

  ret->ConvertToData(&dest->data_);
}

void ImportNode(const aiNode* node, CharacterNodeData* dest)
{
  if (node->mName.length == 0 || strcmp(node->mName.C_Str(), "DummyRootNode") == 0)
  {
    aiVector3D position;
    aiVector3D scaling;
    aiVector3D rotation;
    node->mTransformation.Decompose(scaling, rotation, position);
    dest->position_ = TVec3f(position.x, position.y, position.z);
    dest->scale_ = TVec3f(scaling.x, scaling.y, scaling.z);
    dest->rotation_ = TVec3f(rotation.x, rotation.y, rotation.z);
    ImportNode(node->mChildren[0], dest);
    return;
  }

  dest->name_ = node->mName.C_Str();

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


IAssetDataContainer* CharacterModelAssetConverter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const
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

  aiSetImportPropertyInteger(props, AI_CONFIG_PP_RVC_FLAGS, aiComponent_LIGHTS | aiComponent_CAMERAS | aiComponent_COLORS);

  const aiScene* scene = aiImportFileExWithProperties(
    meta->GetInputPath().c_str(),
    ppsteps | /* configurable pp steps */
    aiProcess_GenSmoothNormals | // generate smooth normal vectors if not existing
    aiProcess_SplitLargeMeshes | // split large, unrenderable meshes into submeshes
    aiProcess_Triangulate | // triangulate polygons with more than 3 edges
    aiProcess_RemoveComponent |
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

  std::vector<SharedRef<AssetEntity>> sub_assets = std::vector<SharedRef<AssetEntity>>();

  // Mesh
  data->mesh_datas_.resize(scene->mNumMeshes);
  for (T_UINT32 i = 0; i < scene->mNumMeshes; ++i)
  {
    aiMesh* mesh = scene->mMeshes[i];
    ImportMesh(meta, scene, mesh, context, &data->mesh_datas_[i]);
    data->mesh_material_indices_.emplace_back(mesh->mMaterialIndex);
  }

  // Material
  std::vector<SharedRef<AssetEntity>> material_entities;
  for (T_UINT32 i = 0; i < scene->mNumMaterials; ++i)
  {
    aiMaterial* mat = scene->mMaterials[i];
    const SharedRef<AssetEntity>& material_asset_entity = context->AddEntity(ImportMaterial(meta, mat, this, context));
    sub_assets.push_back(material_asset_entity);
  }

  for (T_UINT32 i = 0; i < scene->mNumMeshes; ++i)
  {
    aiMesh* mesh = scene->mMeshes[i];
    data->material_unique_ids_.emplace_back(material_entities[mesh->mMaterialIndex]->GetMetaData()->GetUniqueID());
  }

  // Node
  ImportNode(scene->mRootNode, &data->root_node_);

  for (const SharedRef<AssetEntity>& sub_asset : sub_assets)
  {
    sub_asset->Load(context);
    meta->GetConverterSetting()->AddSubAsset(sub_asset->GetMetaData()->GetUniqueID());
  }

  data->name_ = meta->GetURI().GetPrefix();

  aiReleaseImport(scene);

  return new AssetDataContainer<CharacterModelData>(data, this);
}
