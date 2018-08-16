#include "Plane3D.h"
#include "MeshRenderer.h"
#include "EngineAsset.h"

// =================================================================
// Factory Method
// =================================================================
Plane3D* Plane3D::Create()
{
  Plane3D* ret = new Plane3D();
  ret->SetRenderer(MeshRenderer::Create(EngineAsset::rcCustomMesh::PLANE.GetContents(), ret));
  ret->GetRenderer()->SetMaterial(EngineAsset::Material::WHITE);
  return ret;
}
