#pragma once

#include <vector>
#include "INativeProcess_Graphics.h"

class SubMesh;

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
  SubMesh* CreateSubMesh() const;

public:
  virtual T_UINT16 GetVertexesCount() const = 0;
  virtual void SetupVertex(void* dest) const = 0;
  virtual T_UINT16 GetIndicesCount() const = 0;
  virtual const T_UINT16* GetIndices() const = 0;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const = 0;
  virtual Vertex::VertexType GetVertexType() const = 0;

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<SubMesh*> instances_;

};