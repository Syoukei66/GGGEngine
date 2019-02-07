#pragma once

#include <Assimp/scene.h>
#include <Assimp/Importer.hpp>
#include <Assimp/cimport.h>
#include <Assimp/postprocess.h>
#include <Constants/Extensions.h>
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

/*!
 * マテリアルからテクスチャ情報をインポートする
 * @param directory_path ルートディレクトリのパス
 * @param material 対象マテリアル
 * @param type テクスチャタイプ
 * @param i テクスチャ番号
 * @param context
 * @return テクスチャのAssetEntity
 */
static SharedRef<AssetEntity> ImportTexture(const std::string& directory_path, const aiMaterial* material, aiTextureType type, T_UINT32 i, AssetConverterContext* context)
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
    URI uri = URI(directory_path, path.C_Str());
    SharedRef<AssetEntity> entity = context->GetEntity(uri);
    GG_ASSERT(entity, "存在しないテクスチャが指定されました");
    return entity;
  }

  return context->GetEntity(context->GetDefaultAssetURI(DefaultUniqueID::TEXTURE_WHITE));
}

/*!
 * マテリアルからシェーダー情報をインポートする
 * @param material 対象マテリアル
 * @param context
 * @return シェーダーのAssetEntity
 */
static SharedRef<AssetEntity> ImportShader(const aiMaterial* material, AssetConverterContext* context)
{
  T_INT32 mode;
  AssetMetaData* shader_meta_data = nullptr;
  if (AI_SUCCESS == material->Get(AI_MATKEY_SHADING_MODEL, mode))
  {
    return context->GetEntity(context->GetDefaultAssetURI(DefaultUniqueID::DEFAULT_UID_BEGIN + mode));
  }
  return context->GetEntity(context->GetDefaultAssetURI(DefaultUniqueID::SHADER_GOURAUD));
}

/*!
 * マテリアルをインポートする
 * @param material_override 同名のマテリアルが存在する時、上書きをするかどうか
 * @param source_meta_data マテリアルデータが含まれるモデルAssetのMetaData
 * @param material Material情報
 * @param converter マテリアルデータが含まれるモデルのConverter
 * @param context 
 * @return マテリアルのAssetEntity
 */
static SharedRef<AssetEntity> ImportMaterial(bool material_override, AssetMetaData* source_meta_data, const aiMaterial* material, const AssetConverter* converter, AssetConverterContext* context)
{
  aiString name;
  if (AI_SUCCESS != aiGetMaterialString(material, AI_MATKEY_NAME, &name))
  {
    return nullptr;
  }

  MaterialData* data = new MaterialData();

  // マテリアルのURIを作成
  std::string material_directory_path = source_meta_data->GetURI().GetDirectoryPath() + "/Material";
  URI material_uri = URI(material_directory_path, name.C_Str(), Extensions::MATERIAL);
  SharedRef<AssetEntity> entity = context->GetEntity(material_uri);

  // 既に同名のマテリアルAssetが存在し、上書き設定もなければここではインポートは行わない。
  if (entity)
  {
    //TODO:現在は上書きをしない設定にしているが、本来はモデルのConverterSettingで操作できるようにする
    return entity;
  }

  SharedRef<AssetEntity> shader_asset_entity = ImportShader(material, context);
  shader_asset_entity->Load(context);
  const ShaderData* shader_data = shader_asset_entity->GetData<ShaderData>();
  MaterialData::CreateWithShader(
    shader_data->properties_,
    shader_asset_entity->GetMetaData()->GetUniqueID(),
    data
  );

  //Colors
  aiColor4D color;
  //if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
  //{
  //  data->color_ = ToTColor(color);
  //}
  SharedRef<AssetEntity> tex_asset_entity = ImportTexture(source_meta_data->GetURI().GetDirectoryPath(), material, aiTextureType_DIFFUSE, 0, context);
  tex_asset_entity->Load(context);
  data->main_texture_unique_id_ = tex_asset_entity->GetMetaData()->GetUniqueID();

  //TODO:プロパティのインポート処理

  // AssetEntityが存在していなかった場合AssetEntityを新たに作成する
  if (!entity)
  {
    AssetMetaData* meta_data = AssetMetaData::Create(
      material_uri,
      source_meta_data->GetUniqueID(),
      context
    );
    entity = context->AddEntity(AssetEntity::Create(meta_data));
  }

  // 上書き設定が有効な場合、MaterialのAssetファイルを作成し、Assetディレクトリに出力する。
  if (material_override)
  {
    std::string output_path = FileUtil::CreateInputPath(material_uri);
    FileUtil::PrepareDirectory(output_path);
    CerealIO::Json::Export<MaterialData>(output_path.c_str(), data);
  }

  // AssetEntityに中間データやサブアセットを設定する
  entity->SetData(data);
  entity->GetMetaData()->GetConverterSetting()->ClearSubAssets();
  entity->GetMetaData()->GetConverterSetting()->AddSubAsset(tex_asset_entity->GetMetaData()->GetUniqueID());
  entity->GetMetaData()->GetConverterSetting()->AddSubAsset(shader_asset_entity->GetMetaData()->GetUniqueID());

  return entity;
}
