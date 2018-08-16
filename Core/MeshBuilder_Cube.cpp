#include "MeshBuilder_Cube.h"
#include "MeshFactory_Cube.h"

MeshBuilder_Cube::MeshBuilder_Cube(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z, T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z, T_FLOAT tile_count_x, T_FLOAT tile_count_y, T_FLOAT tile_count_z)
  : format(format)
  , scale_x(scale_x)
  , scale_y(scale_y)
  , scale_z(scale_z)
  , resolution_x(resolution_x)
  , resolution_y(resolution_y)
  , resolution_z(resolution_z)
  , tile_count_x(tile_count_x)
  , tile_count_y(tile_count_y)
  , tile_count_z(tile_count_z)
{
}

MeshBuilder_Cube::MeshBuilder_Cube()
  : format()
  , scale_x()
  , scale_y()
  , scale_z()
  , resolution_x()
  , resolution_y()
  , resolution_z()
  , tile_count_x()
  , tile_count_y()
  , tile_count_z()
{
}

rcMesh* MeshBuilder_Cube::CreateMesh() const
{
  return MeshFactory::Cube::Create(
    this->format, 
    this->scale_x, this->scale_y, this->scale_z,
    this->resolution_x, this->resolution_y, this->resolution_z,
    this->tile_count_x, this->tile_count_y, this->tile_count_z
  );
}
