#include "Plane3D.h"
#include <Core/AssetManager.h>
#include "MeshRenderer.h"

// =================================================================
// Factory Method
// =================================================================
Plane3D* Plane3D::Create()
{
  Plane3D* ret = new Plane3D();
  ret->SetRenderer(MeshRenderer::Create(AssetManager::Load<rcMesh>(DefaultUniqueID::MESH_PLANE), ret));
  ret->GetRenderer()->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_WHITE));
  return ret;
}
