#include "Plane3D.h"
#include <Core/AssetManager.h>
#include "MeshRenderer.h"

// =================================================================
// Factory Method
// =================================================================
Plane3D* Plane3D::Create()
{
  Plane3D* ret = new Plane3D();
  ret->SetRenderer(MeshRenderer::Create(AssetManager::GetLoader<rcMesh>(DefaultUniqueID::MESH_PLANE)->CreateFromFile(), ret));
  ret->GetRenderer()->SetMaterial(AssetManager::GetLoader<rcMaterial>(DefaultUniqueID::MATERIAL_WHITE)->CreateFromFile());
  return ret;
}
