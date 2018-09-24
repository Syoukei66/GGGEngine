//#include "AssimpStaticModelImporter.h"
//#include <assimp\mesh.h>
//
//#include "../Core/GraphicsConstants.h"
//#include "../Core/NativeAssert.h"
//#include "../Core/Color.h"
//
//#include "AssetManager.h"
//
//#include "AssimpMathImporter.h"
//#include "AssimpMaterialSystemImporter.h"
//
//namespace ModelImporter
//{
//
//namespace Assimp
//{
//static T_UINT32 ImportTexture(AssetInfo* info, const aiMaterial* material, aiTextureType type)
//{
//  aiString path;
//  aiTextureMapping mapping;
//  T_UINT32 uv_index;
//  T_FLOAT blend;
//  aiTextureOp op;
//  aiTextureMapMode map_mode;
//  T_UINT32 flags;
//
//  T_UINT32 ret = 0;
//  for (T_UINT8 i = 0; i < 8; ++i)
//  {
//    if (AI_SUCCESS == aiGetMaterialTexture(material, type, i, &path, &mapping, &uv_index, &blend, &op, &map_mode, &flags))
//    {
//      NATIVE_ASSERT(ret == 0, "テクスチャが想定していたより多いです");
//      const std::string full_path = info->directory_path + path.C_Str();
//      info->meta_data->references.emplace(full_path);
//      ret = OldAssetManager::GetInstance().GetInfomation(full_path)->meta_data->unique_id;
//    }
//  }
//  return ret;
//}
//
////=============================================================================
//// MaterialData
////=============================================================================
//static void ImportMaterial(AssetInfo* info, const aiMaterial* material, StaticModelMaterialData* dest)
//{
//
//}
//
////=============================================================================
//// ModelData
////=============================================================================
//StaticModelData* ImportStaticModel(AssetInfo* info, const aiScene* scene)
//{
//  NATIVE_ASSERT(scene->mNumMeshes == scene->mNumMaterials, "思ってたのと違う");
//
//  //参照をクリア
//  info->meta_data->references.clear();
//
//  ret->material_count_ = ret->submesh_count_;
//  ret->materials_ = new StaticModelMaterialData[ret->material_count_]();
//
//  for (T_INT32 i = 0; i < ret->material_count_; ++i)
//  {
//    ImportMaterial(info, scene->mMaterials[i], &ret->materials_[i]);
//  }
//
//  return ret;
//}
//
//} // namespace Assimp
//
//} // namespace ModelImporter