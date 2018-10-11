#pragma once

#include "MeshBuilder.h"

class MeshBuilder_Sprite : public MeshBuilder
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshBuilder_Sprite();

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual MeshData* CreateMesh() const override;

  // =================================================================
  // Serializer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
  }

};
CEREAL_CLASS_VERSION(MeshBuilder_Sprite, 1);