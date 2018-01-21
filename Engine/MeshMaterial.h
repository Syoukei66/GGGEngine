#pragma once

#include "INativeProcess_Graphics.h"

class MeshMaterial
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual void SetupVertex(void* dest) const = 0;
  virtual T_UINT16 GetVertexesCount() const = 0;
  virtual const void* GetVertexes() const = 0;
  virtual T_UINT16 GetIndicesCount() const = 0;
  virtual const T_UINT16* GetIndices() const = 0;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const = 0;
  virtual Vertex::VertexType GetVertexType() const = 0;

};