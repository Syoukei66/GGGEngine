#pragma once

#include "Mesh.h"

class MeshBuilder
{
public:
  virtual rcMesh* CreateMesh(bool read_only) const = 0;
};
