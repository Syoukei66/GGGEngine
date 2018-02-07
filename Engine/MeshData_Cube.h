#pragma once

#include "MeshData.h"

class MeshData_Cube : public MeshData
{
public:
  static MeshData_Cube& GetInstance()
  {
    static MeshData_Cube ret;
    return ret;
  }

private:
  MeshData_Cube() {}
  MeshData_Cube(const MeshData_Cube& b) {}

public:
  virtual T_UINT16 GetVertexesCount() const override;
  virtual void SetupVertex(void* dest) const override;
  virtual T_UINT16 GetIndicesCount() const override;
  virtual const T_UINT16* GetIndices() const override;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const override;
  virtual Vertex::VertexType GetVertexType() const override;

};