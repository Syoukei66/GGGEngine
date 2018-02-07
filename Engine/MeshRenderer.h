#pragma once

#include "Renderer.h"
#include "Mesh.h"

class MeshRenderer : public Renderer
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static MeshRenderer* Create(const Mesh& mesh, GameObject* entity);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  MeshRenderer(GameObject* entity);

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void EditProperty(T_UINT8 material_index, T_UINT8 pass_index, Material* material) override;
  virtual void DrawSubset(T_UINT8 material_index, T_UINT8 pass_index) override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetMesh(const Mesh& mesh)
  {
    this->mesh_ = &mesh;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const Mesh* mesh_;

};