#pragma once

#include "MeshBuilder.h"

class MeshBuilder_UvSphere : public MeshBuilder
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshBuilder_UvSphere(T_UINT32 format, T_FLOAT scale, T_UINT32 resolution_x = 4, T_UINT32 resolution_y = 4);
  MeshBuilder_UvSphere();

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual UniqueRef<rcDynamicMesh> CreateMesh() const override;

  // =================================================================
  // Serializer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("Format", this->format_));
    ar(cereal::make_nvp("Scale", this->scale_));
    ar(cereal::make_nvp("ResolutionX", this->resolution_x_));
    ar(cereal::make_nvp("ResolutionY", this->resolution_y_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  T_UINT32 format_;
  T_FLOAT scale_;
  T_UINT32 resolution_x_;
  T_UINT32 resolution_y_;

};
CEREAL_CLASS_VERSION(MeshBuilder_UvSphere, 1);