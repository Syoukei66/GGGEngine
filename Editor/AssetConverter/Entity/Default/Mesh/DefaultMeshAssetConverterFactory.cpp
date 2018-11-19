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

  return ret;
}
