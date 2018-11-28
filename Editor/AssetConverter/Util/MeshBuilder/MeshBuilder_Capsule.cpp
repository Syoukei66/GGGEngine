#include "MeshBuilder_Capsule.h"

MeshBuilder_Capsule::MeshBuilder_Capsule(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z, T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z, T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z, T_UINT32 roundness)
  : format_(format)
  , scale_x_(scale_x)
  , scale_y_(scale_y)
  , scale_z_(scale_z)
  , resolution_x_(resolution_x)
  , resolution_y_(resolution_y)
  , resolution_z_(resolution_z)
  , tile_count_x_(tile_count_x)
  , tile_count_y_(tile_count_y)
  , tile_count_z_(tile_count_z)
  , roundness_(roundness) 
{
}

MeshBuilder_Capsule::MeshBuilder_Capsule()
  : format_(Vertex::V_FORMAT_PNUT)
  , scale_x_(1.0f)
  , scale_y_(3.0f)
  , scale_z_(1.0f)
  , resolution_x_(6)
  , resolution_y_(12)
  , resolution_z_(6)
  , tile_count_x_(1.0f)
  , tile_count_y_(1.0f)
  , tile_count_z_(1.0f)
  , roundness_(3)
{
}

UniqueRef<rcDynamicMesh> MeshBuilder_Capsule::CreateMesh() const
{
  return MeshFactory::CubeSphere::Create(
    this->format_,
    this->scale_x_, this->scale_y_, this->scale_z_,
    this->resolution_x_, this->resolution_y_, this->resolution_z_,
    this->tile_count_x_, this->tile_count_y_, this->tile_count_z_,
    this->roundness_
  );
}
