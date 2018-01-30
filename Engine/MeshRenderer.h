#pragma once

#include "Renderer.h"
#include "Mesh.h"

class MeshRenderer : public Renderer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshRenderer();
  ~MeshRenderer();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Draw(GameObjectRenderState* state) override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetMesh(Mesh* mesh)
  {
    this->mesh_ = mesh;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Mesh* mesh_;

};