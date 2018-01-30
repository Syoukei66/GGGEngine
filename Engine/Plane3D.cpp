#include "Plane3D.h"
#include "EngineAsset.h"
#include "MeshMaterial_Plane.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Plane3D::Plane3D()
{
  this->SetMaterial(EngineAsset::Material::MODEL);
  this->mesh_material_ = new MeshData_Plane();
  this->mesh_ = new Mesh(*this->mesh_material_);
}

Plane3D::~Plane3D()
{
  delete this->mesh_;
  delete this->mesh_material_;
}

void Plane3D::NativeDraw(GameObject3DRenderState* state)
{
  this->mesh_->DrawSubset();
}
