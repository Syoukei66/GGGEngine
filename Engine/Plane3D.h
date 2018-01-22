#pragma once

#include "GameObject3D.h"
#include "Mesh.h"

class Plane3D : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Plane3D();
  ~Plane3D();

public:
  void NativeDraw(GameObject3DRenderState* state) override;

private:
  MeshMaterial* mesh_material_;
  Mesh* mesh_;

};
