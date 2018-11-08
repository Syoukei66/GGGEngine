#pragma once

class MeshBuilder
{
public:
  virtual MeshData* CreateMesh() const = 0;
};
