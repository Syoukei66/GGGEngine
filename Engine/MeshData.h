#pragma once

#include <vector>
#include "INativeProcess_Graphics.h"
#include "Mesh.h"

class MeshData
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshData();
  ~MeshData();

  // =================================================================
  // Method
  // =================================================================
public:
  Mesh* CreateMesh() const;

public:
  virtual T_UINT32 GetVertexCount() const = 0;
  virtual T_UINT32 GetIndexCount() const = 0;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const = 0;
  virtual T_UINT32 GetVertexFormat() const = 0;
  virtual void SetupMesh(Mesh* dest) const = 0;

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<Mesh*> instances_;

};