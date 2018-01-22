#pragma once

#include <fbxsdk.h>
#include "MeshMaterial.h"

class FbxMeshMaterial : public MeshMaterial
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FbxMeshMaterial(FbxMesh* mesh);
  ~FbxMeshMaterial();

  // =================================================================
  // Method for/from Interface/SuperClass
  // =================================================================
public:
  virtual T_UINT16 GetPolygonCount() const override;
  virtual T_UINT16 GetVertexesCount() const override;
  virtual void SetupVertex(void* dest) const override;
  virtual T_UINT16 GetIndicesCount() const override;
  virtual const T_UINT16* GetIndices() const override;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const override;
  virtual Vertex::VertexType GetVertexType() const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT16 polygon_count_;
  Vertex::VC* vertexes_;
  T_UINT16 vertexes_count_;
  T_UINT16* indices_;
  T_UINT16 indices_count_;

};