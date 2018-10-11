#include "Cube3D.h"
#include "MeshRenderer.h"
#include <Core/AssetManager.h>

// =================================================================
// Factory Method
// =================================================================
Cube3D* Cube3D::Create()
{
  Cube3D* ret = new Cube3D();
  ret->SetRenderer(MeshRenderer::Create(AssetManager::GetLoader<rcMesh>(DefaultUniqueID::MESH_CUBE)->CreateFromFile(), ret));
  ret->GetRenderer()->SetMaterial(AssetManager::GetLoader<rcMaterial>(DefaultUniqueID::MATERIAL_WHITE)->CreateFromFile());
  return ret;
}
