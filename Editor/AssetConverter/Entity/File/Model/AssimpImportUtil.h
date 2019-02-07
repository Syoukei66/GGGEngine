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
 * �}�e���A������e�N�X�`�������C���|�[�g����
 * @param directory_path ���[�g�f�B���N�g���̃p�X
 * @param material �Ώۃ}�e���A��
 * @param type �e�N�X�`���^�C�v
 * @param i �e�N�X�`���ԍ�
 * @param context
 * @return �e�N�X�`����AssetEntity
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
    GG_ASSERT(entity, "���݂��Ȃ��e�N�X�`�����w�肳��܂���");
    return entity;
  }

  return context->GetEntity(context->GetDefaultAssetURI(DefaultUniqueID::TEXTURE_WHITE));
}

/*!
 * �}�e���A������V�F�[�_�[�����C���|�[�g����
 * @param material �Ώۃ}�e���A��
 * @param context
 * @return �V�F�[�_�[��AssetEntity
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
 * �}�e���A�����C���|�[�g����
 * @param material_override �����̃}�e���A�������݂��鎞�A�㏑�������邩�ǂ���
 * @param source_meta_data �}�e���A���f�[�^���܂܂�郂�f��Asset��MetaData
 * @param material Material���
 * @param converter �}�e���A���f�[�^���܂܂�郂�f����Converter
 * @param context 
 * @return �}�e���A����AssetEntity
 */
static SharedRef<AssetEntity> ImportMaterial(bool material_override, AssetMetaData* source_meta_data, const aiMaterial* material, const AssetConverter* converter, AssetConverterContext* context)
{
  aiString name;
  if (AI_SUCCESS != aiGetMaterialString(material, AI_MATKEY_NAME, &name))
  {
    return nullptr;
  }

  MaterialData* data = new MaterialData();

  // �}�e���A����URI���쐬
  std::string material_directory_path = source_meta_data->GetURI().GetDirectoryPath() + "/Material";
  URI material_uri = URI(material_directory_path, name.C_Str(), Extensions::MATERIAL);
  SharedRef<AssetEntity> entity = context->GetEntity(material_uri);

  // ���ɓ����̃}�e���A��Asset�����݂��A�㏑���ݒ���Ȃ���΂����ł̓C���|�[�g�͍s��Ȃ��B
  if (entity)
  {
    //TODO:���݂͏㏑�������Ȃ��ݒ�ɂ��Ă��邪�A�{���̓��f����ConverterSetting�ő���ł���悤�ɂ���
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

  //TODO:�v���p�e�B�̃C���|�[�g����

  // AssetEntity�����݂��Ă��Ȃ������ꍇAssetEntity��V���ɍ쐬����
  if (!entity)
  {
    AssetMetaData* meta_data = AssetMetaData::Create(
      material_uri,
      source_meta_data->GetUniqueID(),
      context
    );
    entity = context->AddEntity(AssetEntity::Create(meta_data));
  }

  // �㏑���ݒ肪�L���ȏꍇ�AMaterial��Asset�t�@�C�����쐬���AAsset�f�B���N�g���ɏo�͂���B
  if (material_override)
  {
    std::string output_path = FileUtil::CreateInputPath(material_uri);
    FileUtil::PrepareDirectory(output_path);
    CerealIO::Json::Export<MaterialData>(output_path.c_str(), data);
  }

  // AssetEntity�ɒ��ԃf�[�^��T�u�A�Z�b�g��ݒ肷��
  entity->SetData(data);
  entity->GetMetaData()->GetConverterSetting()->ClearSubAssets();
  entity->GetMetaData()->GetConverterSetting()->AddSubAsset(tex_asset_entity->GetMetaData()->GetUniqueID());
  entity->GetMetaData()->GetConverterSetting()->AddSubAsset(shader_asset_entity->GetMetaData()->GetUniqueID());

  return entity;
}
