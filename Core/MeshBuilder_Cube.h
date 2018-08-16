#pragma once

#include "MeshBuilder.h"

class MeshBuilder_Cube : public MeshBuilder
{
public:
  MeshBuilder_Cube(
    T_UINT32 format, 
    T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z,
    T_UINT32 resolution_x, T_UINT32 resolution_y, T_UINT32 resolution_z,
    T_FLOAT tile_count_x = 1.0f, T_FLOAT tile_count_y = 1.0f, T_FLOAT tile_count_z = 1.0f
  );
  MeshBuilder_Cube();

public:
  virtual rcCustomMesh* CreateMesh() const override;

public:
  T_UINT32 format;
  T_FLOAT scale_x;
  T_FLOAT scale_y;
  T_FLOAT scale_z;
  T_UINT32 resolution_x;
  T_UINT32 resolution_y;
  T_UINT32 resolution_z;
  T_FLOAT tile_count_x;
  T_FLOAT tile_count_y;
  T_FLOAT tile_count_z;

};