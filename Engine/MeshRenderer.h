#pragma once

#include <Core/Mesh.h>

#include "Renderer.h"

class MeshRenderer : public Renderer
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static MeshRenderer* Create(const rcMesh* mesh, GameObject* entity);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  MeshRenderer(GameObject* entity);

  // =================================================================
  // Method
  // =================================================================
protected:
  virtual bool SetStreamSource() const override;
  virtual void SetProperties(rcShader* shader) const override;
  virtual void DrawSubset(T_UINT8 submesh_index) const override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetMesh(const rcMesh& mesh)
  {
    this->mesh_ = &mesh;
  }
  inline void SetMesh(const rcMesh* mesh)
  {
    this->mesh_ = mesh;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const rcMesh* mesh_;

};