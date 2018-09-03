#pragma once

#include "Renderer.h"
#include "Mesh.h"

class MeshRenderer : public Renderer
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static MeshRenderer* Create(const rcCustomMesh& mesh, GameObject* entity);
  static MeshRenderer* Create(const rcCustomMesh* mesh, GameObject* entity);

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
  virtual void SetProperties(rcMaterial* material) const override;
  virtual void DrawSubset(T_UINT8 submesh_index) const override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetMesh(const rcCustomMesh& mesh)
  {
    this->mesh_ = &mesh;
  }
  inline void SetMesh(const rcCustomMesh* mesh)
  {
    this->mesh_ = mesh;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const rcCustomMesh* mesh_;

};