#include "MeshBuilder_Plane.h"
#include "MeshFactory_Plane.h"

MeshBuilder_Plane::MeshBuilder_Plane(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y, T_FLOAT tile_count_x, T_FLOAT tile_count_y)
  : format(format)
  , scale_x(scale_x)
  , scale_y(scale_y)
  , resolution_x(resolution_x)
  , resolution_y(resolution_y)
  , tile_count_x(tile_count_x)
  , tile_count_y(tile_count_y)
{
}

MeshBuilder_Plane::MeshBuilder_Plane()
  : format()
  , scale_x()
  , scale_y()
  , resolution_x()
  , resolution_y()
  , tile_count_x()
  , tile_count_y()
{
}

rcCustomMesh* MeshBuilder_Plane::CreateMesh() const
{
  return MeshFactory::Plane::Create(format, scale_x, scale_y, resolution_x, resolution_y, tile_count_x, tile_count_y);
}

