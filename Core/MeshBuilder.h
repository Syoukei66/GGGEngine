#pragma once

#include "CustomMesh.h"
#include "StaticMesh.h"

class MeshBuilder
{
public:
  virtual rcCustomMesh* CreateMesh() const = 0;
  rcStaticMesh* CreateStaticMesh() const
  {
    rcCustomMesh* mesh = this->CreateMesh();
    rcStaticMesh* ret = mesh->MoveStatic();
    mesh->Release();
    return ret;
  }
};
