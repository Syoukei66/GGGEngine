#pragma once

#include <Core/MeshData.h>

class MeshBuilder
{
public:
  virtual MeshData* CreateMesh() const = 0;
};
