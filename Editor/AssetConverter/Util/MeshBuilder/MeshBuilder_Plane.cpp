#include "MeshBuilder_Plane.h"

MeshBuilder_Plane::MeshBuilder_Plane(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y, T_FLOAT tile_count_x, T_FLOAT tile_count_y)
  : format_(format)
  , scale_x_(scale_x)
  , scale_y_(scale_y)
  , resolution_x_(resolution_x)
  , resolution_y_(resolution_y)
  , tile_count_x_(tile_count_x)
  , tile_count_y_(tile_count_y)
{
}

MeshBuilder_Plane::MeshBuilder_Plane()
  : format_(Vertex::V_FORMAT_PNUT)
  , scale_x_(1.0f)
  , scale_y_(1.0f)
  , resolution_x_(1)
  , resolution_y_(1)
  , tile_count_x_(1.0f)
  , tile_count_y_(1.0f)
{
}

UniqueRef<rcDynamicMesh> MeshBuilder_Plane::CreateMesh() const
{
  return MeshFactory::Plane::Create(
    format_,
    scale_x_, scale_y_,
    resolution_x_, resolution_y_,
    tile_count_x_, tile_count_y_
  );
}
