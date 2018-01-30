#pragma once

#include "MeshData.h"

class MeshMaterial_Cube : public MeshData
{
public:
  MeshMaterial_Cube();

public:
  virtual T_UINT16 GetVertexesCount() const override;
  virtual void SetupVertex(void * dest) const override;
  virtual T_UINT16 GetIndicesCount() const override;
  virtual const T_UINT16 * GetIndices() const override;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const override;
  virtual Vertex::VertexType GetVertexType() const override;
};