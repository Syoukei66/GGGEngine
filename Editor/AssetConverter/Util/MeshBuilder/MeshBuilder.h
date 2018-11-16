#pragma once

class MeshBuilder
{
public:
  virtual UniqueRef<rcMesh> CreateMesh() const = 0;
};
