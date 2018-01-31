#include "Plane3D.h"
#include "MeshRenderer.h"
#include "EngineAsset.h"

// =================================================================
// Factory Method
// =================================================================
Plane3D* Plane3D::Create()
{
  Plane3D* ret = new Plane3D();
  ret->SetRenderer(MeshRenderer::Create(EngineAsset::Mesh::PLANE.GetContents(), ret));
  return ret;
}
