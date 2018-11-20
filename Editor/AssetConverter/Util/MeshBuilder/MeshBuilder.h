#pragma once

class MeshBuilder
{
public:
  virtual UniqueRef<rcDynamicMesh> CreateMesh() const = 0;
};
