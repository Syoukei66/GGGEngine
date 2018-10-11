#pragma once

#include <Cereal/cereal.hpp>
#include "MeshBuilder_Cube.h"
#include "MeshBuilder_Plane.h"
#include "MeshBuilder_Sprite.h"

#include "AssetConverterFactory.h"

class DefaultMeshAssetConverterFactory : public AssetConverterFactory
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DefaultMeshAssetConverterFactory() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  IAssetConverter* Create(AssetConverterContext* context) const override;

  // =================================================================
  // Serializer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("Cube", this->cube_));
    ar(cereal::make_nvp("Plane", this->plane_));
    ar(cereal::make_nvp("Sprite", this->sprite_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MeshBuilder_Cube cube_;
  MeshBuilder_Plane plane_;
  MeshBuilder_Sprite sprite_;

};
CEREAL_CLASS_VERSION(DefaultMeshAssetConverterFactory, 1);
