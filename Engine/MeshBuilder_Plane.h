#pragma once

#include "MeshBuilder.h"

class MeshBuilder_Plane : public MeshBuilder
{
public:
  MeshBuilder_Plane(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y, T_FLOAT tile_count_x = 1.0f, T_FLOAT tile_count_y = 1.0f);
  MeshBuilder_Plane();

public:
  virtual Mesh* Create() const override;

public:
  T_UINT32 format;
  T_FLOAT scale_x;
  T_FLOAT scale_y;
  T_UINT32 resolution_x;
  T_UINT32 resolution_y;
  T_FLOAT tile_count_x;
  T_FLOAT tile_count_y;

};