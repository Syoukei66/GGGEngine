#include "Cube3D.h"
#include "MeshRenderer.h"
#include <Core/AssetManager.h>

// =================================================================
// Factory Method
// =================================================================
Cube3D* Cube3D::Create()
{
  Cube3D* ret = new Cube3D();
  ret->SetRenderer(MeshRenderer::Create(AssetManager::Load<rcMesh>(DefaultUniqueID::MESH_CUBE), ret));
  ret->GetRenderer()->SetMaterial(AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_WHITE));
  return ret;
}
