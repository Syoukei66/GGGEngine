#pragma once

#include "MeshData.h"

class MeshData_Sprite : public MeshData
{
public:
  static MeshData_Sprite& GetInstance()
  {
    static MeshData_Sprite ret;
    return ret;
  }

private:
  MeshData_Sprite() {}
  MeshData_Sprite(const MeshData_Sprite& b) {}

public:
  virtual T_UINT16 GetVertexesCount() const override;
  virtual void SetupVertex(void* dest) const override;
  virtual T_UINT16 GetIndicesCount() const override;
  virtual const T_UINT16* GetIndices() const override;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const override;
  virtual Vertex::VertexType GetVertexType() const override;
};