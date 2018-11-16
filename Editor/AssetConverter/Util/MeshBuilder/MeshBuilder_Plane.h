#pragma once

#include "MeshBuilder.h"

class MeshBuilder_Plane : public MeshBuilder
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshBuilder_Plane(
    T_UINT32 format,
    T_FLOAT scale_x, T_FLOAT scale_y,
    T_UINT32 resolution_x, T_UINT32 resolution_y,
    T_FLOAT tile_count_x = 1.0f, T_FLOAT tile_count_y = 1.0f
  );
  MeshBuilder_Plane();

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual UniqueRef<rcMesh> CreateMesh() const override;

  // =================================================================
  // Serializer
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("Format", this->format_));
    ar(cereal::make_nvp("ScaleX", this->scale_x_));
    ar(cereal::make_nvp("ScaleY", this->scale_y_));
    ar(cereal::make_nvp("ResolutionX", this->resolution_x_));
    ar(cereal::make_nvp("ResolutionY", this->resolution_y_));
    ar(cereal::make_nvp("TitleCountX", this->tile_count_x_));
    ar(cereal::make_nvp("TitleCountY", this->tile_count_y_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  T_UINT32 format_;
  T_FLOAT scale_x_;
  T_FLOAT scale_y_;
  T_UINT32 resolution_x_;
  T_UINT32 resolution_y_;
  T_FLOAT tile_count_x_;
  T_FLOAT tile_count_y_;

};
CEREAL_CLASS_VERSION(MeshBuilder_Plane, 1);