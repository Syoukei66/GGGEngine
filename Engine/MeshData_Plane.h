#pragma once

#include "MeshData.h"

class MeshData_Plane : public MeshData
{
public:
  static MeshData_Plane& GetInstance()
  {
    static MeshData_Plane ret;
    return ret;
  }

private:
  MeshData_Plane() {}
  MeshData_Plane(const MeshData_Plane& b) {}

public:
  virtual T_UINT16 GetVertexesCount() const override;
  virtual void SetupVertex(void* dest) const override;
  virtual T_UINT16 GetIndicesCount() const override;
  virtual const T_UINT16* GetIndices() const override;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const override;
  virtual Vertex::VertexType GetVertexType() const override;
};