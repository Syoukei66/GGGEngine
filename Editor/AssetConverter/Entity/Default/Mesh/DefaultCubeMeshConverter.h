#pragma once

#include <Entity/Default/DefaultAssetConverter.h>

class DefaultCubeMeshConverter : public DefaultAssetConverter<rcMesh, StaticMeshData>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefaultCubeMeshConverter(
    const std::string& id,
    const std::string& class_name
  )
    : DefaultAssetConverter<rcMesh, StaticMeshData>(id, class_name)
  {}

  // =================================================================
  // Methods from AssetConverter
  // =================================================================
public:
  virtual IAssetDataContainer* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const override
  {
    StaticMeshData* cube_mesh = new StaticMeshData();
    this->cube_.CreateMesh()->ConvertToData(cube_mesh);
    return new AssetDataContainer<StaticMeshData>(cube_mesh, this);
  }

};
