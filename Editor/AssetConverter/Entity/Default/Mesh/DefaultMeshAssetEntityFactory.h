#pragma once

#include <Cereal/cereal.hpp>
#include <Util/MeshBuilder/MeshBuilder_Cube.h>
#include <Util/MeshBuilder/MeshBuilder_Plane.h>
#include <Util/MeshBuilder/MeshBuilder_Capsule.h>
#include <Util/MeshBuilder/MeshBuilder_CubeSphere.h>
#include <Util/MeshBuilder/MeshBuilder_UvSphere.h>

class AssetConverter;
class AssetConverterContext;

class DefaultMeshAssetEntityFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefaultMeshAssetEntityFactory() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  void Create(AssetConverter* converter, AssetConverterContext* context) const;

  // =================================================================
  // Serializer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("Cube", this->cube_));
    ar(cereal::make_nvp("Plane", this->plane_));
    ar(cereal::make_nvp("Capsule", this->capsule_));
    ar(cereal::make_nvp("CubeSphere", this->cube_sphere_));
    ar(cereal::make_nvp("UvSphere", this->uv_sphere_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MeshBuilder_Cube cube_;
  MeshBuilder_Plane plane_;
  MeshBuilder_Capsule capsule_;
  MeshBuilder_CubeSphere cube_sphere_;
  MeshBuilder_UvSphere uv_sphere_;

};
CEREAL_CLASS_VERSION(DefaultMeshAssetEntityFactory, 1);
