#pragma once

#include "Mesh.h"

class MeshBuilder
{
public:
  virtual Mesh* Create() const = 0;
};
