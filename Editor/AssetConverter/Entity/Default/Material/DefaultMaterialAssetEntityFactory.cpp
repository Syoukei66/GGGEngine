#include "DefaultMaterialAssetEntityFactory.h"

#include <Entity/Default/DefaultAsset.h>
#include <Entity/AssetEntity.h>
#include <Converter/AssetConverterContext.h>

void DefaultMaterialAssetEntityFactory::Create(AssetConverter* converter, AssetConverterContext* context)
{
  using namespace DefaultAsset;
  using namespace DefaultUniqueID;

  // Gouraud
  {
    const SharedRef<AssetEntity>& shader = context->GetEntity(SHADER_GOURAUD);
    shader->Load(context);
    const T_UINT32 shader_uid = shader->GetMetaData()->GetUniqueID();
    MaterialData* mat = new MaterialData();
    MaterialData::CreateWithShader(shader->GetData<ShaderData>()->properties_, shader_uid, mat);
    AssetMetaData* meta = AssetMetaData::Create(MATERIAL_PATH_LAMBERT, converter, context);
    meta->GetConverterSetting()->AddSubAsset(mat->shader_unique_id_);
    context->AddEntity(AssetEntity::Create(meta, mat));
  }
  // Flat
  {
    const SharedRef<AssetEntity>& shader = context->GetEntity(SHADER_FLAT);
    shader->Load(context);
    const T_UINT32 shader_uid = shader->GetMetaData()->GetUniqueID();
    MaterialData* mat = new MaterialData();
    MaterialData::CreateWithShader(shader->GetData<ShaderData>()->properties_, shader_uid, mat);
    AssetMetaData* meta = AssetMetaData::Create(MATERIAL_PATH_UNLIT, converter, context);
    meta->GetConverterSetting()->AddSubAsset(mat->shader_unique_id_);
    context->AddEntity(AssetEntity::Create(meta, mat));
  }
  // NoShading
  {
    const SharedRef<AssetEntity>& shader = context->GetEntity(SHADER_NO_SHADING);
    shader->Load(context);
    const T_UINT32 shader_uid = shader->GetMetaData()->GetUniqueID();
    MaterialData* mat = new MaterialData();
    MaterialData::CreateWithShader(shader->GetData<ShaderData>()->properties_, shader_uid, mat);
    AssetMetaData* meta = AssetMetaData::Create(MATERIAL_PATH_WHITE, converter, context);
    meta->GetConverterSetting()->AddSubAsset(mat->shader_unique_id_);
    context->AddEntity(AssetEntity::Create(meta, mat));
  }

}
