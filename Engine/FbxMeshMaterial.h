#pragma once

#include <fbxsdk.h>
#include "MeshData.h"

class FbxMeshMaterial : public MeshData
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
  virtual T_UINT32 GetVertexCount() const override;
  virtual T_UINT32 GetIndexCount() const override;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() const override;
  virtual T_UINT32 GetVertexFormat() const override;
  virtual void SetupMesh(Mesh* dest) const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  Vertex::VNCT* vertexes_;
  T_UINT16 vertexes_count_;
  T_UINT16* indices_;
  T_UINT16 indices_count_;

};