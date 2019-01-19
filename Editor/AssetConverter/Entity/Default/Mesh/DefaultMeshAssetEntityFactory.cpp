#include "DefaultMeshAssetEntityFactory.h"

#include <Converter/AssetConverterContext.h>
#include <Entity/Default/DefaultAsset.h>
#include <Entity/Default/DefaultAssetConverter.h>
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
void DefaultMeshAssetEntityFactory::Create(AssetConverter* converter, AssetConverterContext* context) const
{
  using namespace DefaultAsset;

  StaticMeshData* cube_mesh = new StaticMeshData();
  this->cube_.CreateMesh()->ConvertToData(cube_mesh);
  context->AddEntity(AssetEntity::Create(AssetMetaData::Create(MESH_PATH_CUBE, converter, context), cube_mesh));

  StaticMeshData* plane_mesh = new StaticMeshData();
  this->plane_.CreateMesh()->ConvertToData(plane_mesh);
  context->AddEntity(AssetEntity::Create(AssetMetaData::Create(MESH_PATH_PLANE, converter, context), plane_mesh));

  StaticMeshData* capsule_mesh = new StaticMeshData();
  this->capsule_.CreateMesh()->ConvertToData(capsule_mesh);
  context->AddEntity(AssetEntity::Create(AssetMetaData::Create(MESH_PATH_CAPSULE, converter, context), capsule_mesh));

  StaticMeshData* cube_sphere_mesh = new StaticMeshData();
  this->cube_sphere_.CreateMesh()->ConvertToData(cube_sphere_mesh);
  context->AddEntity(AssetEntity::Create(AssetMetaData::Create(MESH_PATH_CUBE_SPHERE, converter, context), cube_sphere_mesh));

  StaticMeshData* uv_sphere_mesh = new StaticMeshData();
  this->uv_sphere_.CreateMesh()->ConvertToData(uv_sphere_mesh);
  context->AddEntity(AssetEntity::Create(AssetMetaData::Create(MESH_PATH_UV_SPHERE, converter, context), uv_sphere_mesh));

}
