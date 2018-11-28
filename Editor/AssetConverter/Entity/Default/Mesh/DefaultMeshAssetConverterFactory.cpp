#include "DefaultMeshAssetConverterFactory.h"

#include "DefaultMeshAssetEntity.h"
#include "DefaultMeshAssetExporter.h"
#include <Entity/Default/DefaultAsset.h>
#include <Converter/AssetConverter.h>

// =================================================================
// Methods
// =================================================================
IAssetConverter* DefaultMeshAssetConverterFactory::Create(AssetConverterContext* context) const
{
  DefaultMeshAssetExporter* exporter = new DefaultMeshAssetExporter();
  AssetProgramGenerator<DefaultMeshAssetEntity>* program_generator = new AssetProgramGenerator<DefaultMeshAssetEntity>(2, 0);
  program_generator->AddAsset("DefaultMesh", "rcMesh");
  AssetConverter<DefaultMeshAssetEntity>* ret = new AssetConverter<DefaultMeshAssetEntity>(nullptr, exporter, program_generator);

  using namespace DefaultAsset;

  StaticMeshData* cube_mesh = new StaticMeshData();
  this->cube_.CreateMesh()->ConvertToData(cube_mesh);
  ret->AddEntity(DefaultMeshAssetEntity::Create(AssetMetaData::Create(MESH_PATH_CUBE, context), cube_mesh));

  StaticMeshData* plane_mesh = new StaticMeshData();
  this->plane_.CreateMesh()->ConvertToData(plane_mesh);
  ret->AddEntity(DefaultMeshAssetEntity::Create(AssetMetaData::Create(MESH_PATH_PLANE, context), plane_mesh));

  StaticMeshData* capsule_mesh = new StaticMeshData();
  this->capsule_.CreateMesh()->ConvertToData(capsule_mesh);
  ret->AddEntity(DefaultMeshAssetEntity::Create(AssetMetaData::Create(MESH_PATH_CAPSULE, context), capsule_mesh));

  StaticMeshData* cube_sphere_mesh = new StaticMeshData();
  this->cube_sphere_.CreateMesh()->ConvertToData(cube_sphere_mesh);
  ret->AddEntity(DefaultMeshAssetEntity::Create(AssetMetaData::Create(MESH_PATH_CUBE_SPHERE, context), cube_sphere_mesh));

  StaticMeshData* uv_sphere_mesh = new StaticMeshData();
  this->uv_sphere_.CreateMesh()->ConvertToData(uv_sphere_mesh);
  ret->AddEntity(DefaultMeshAssetEntity::Create(AssetMetaData::Create(MESH_PATH_UV_SPHERE, context), uv_sphere_mesh));

  return ret;
}
