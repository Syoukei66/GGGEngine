#pragma once

#include <Assimp/scene.h>
#include <Assimp/Importer.hpp>
#include <Assimp/cimport.h>
#include <Assimp/postprocess.h>

#include <Entity/File/Model/Material/ModelMaterialAssetEntity.h>
#include <Entity/File/Raw/Texture/TextureAssetEntity.h>
#include <Entity/File/Shader/ShaderAssetEntity.h>

#include <Entity/Default/DefaultAsset.h>

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

static SharedRef<TextureAssetEntity> ImportTexture(const AssetMetaData* model_asset_info, const aiMaterial* material, aiTextureType type, T_UINT32 i, AssetConverterContext* context)
{
  aiString path;
  //aiTextureMapping mapping;
  //T_UINT32 uv_index;
  //T_FLOAT blend;
  //aiTextureOp op;
  //aiTextureMapMode map_mode;
  //T_UINT32 flags;

  if (AI_SUCCESS == aiGetMaterialTexture(material, type, i, &path))
  {
    URI uri = URI(model_asset_info->GetURI().GetDirectoryPath(), path.C_Str());
    return context->ImportImmediately<TextureAssetEntity>(uri, false);
  }

  return nullptr;
}

static SharedRef<ShaderAssetEntity> ImportShader(const AssetMetaData* meta, const aiMaterial* material, AssetConverterContext* context)
{
  T_INT32 mode;
  AssetMetaData* shader_meta_data = nullptr;
  if (AI_SUCCESS == material->Get(AI_MATKEY_SHADING_MODEL, mode))
  {
    //return context->ImportImmediately<ShaderAssetEntity>(context->GetDefaultAssetURI(DefaultUniqueID::DEFAULT_UID_BEGIN + mode), false);
  }
  return context->ImportImmediately<ShaderAssetEntity>(context->GetDefaultAssetURI(DefaultUniqueID::SHADER_GOURAUD), false);
}

static SharedRef<ModelMaterialAssetEntity> ImportMaterial(AssetMetaData* meta, const aiMaterial* material, AssetConverterContext* context)
{
  MaterialData* data = new MaterialData();

  //Colors
  aiColor4D color;
  //if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
  //{
  //  data->color_ = ToTColor(color);
  //}
  SharedRef<TextureAssetEntity> tex_asset_entity = ImportTexture(meta, material, aiTextureType_DIFFUSE, 0, context);
  data->main_texture_unique_id_ = tex_asset_entity ? tex_asset_entity->GetMetaData()->GetUniqueID() : DefaultUniqueID::TEXTURE_WHITE;

  SharedRef<ShaderAssetEntity> shader_asset_entity = ImportShader(meta, material, context);
  data->shader_unique_id_ = shader_asset_entity->GetMetaData()->GetUniqueID();

  //TODO:プロパティのインポート処理
  const SharedRef<ModelMaterialAssetEntity>& entity = ModelMaterialAssetEntity::Create(meta, data);
  entity->AddSubEntity(tex_asset_entity);
  entity->AddSubEntity(shader_asset_entity);

  return entity;
}
