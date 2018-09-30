#include "Cube3D.h"
#include "MeshRenderer.h"
#include <Core/AssetManager.h>

// =================================================================
// Factory Method
// =================================================================
Cube3D* Cube3D::Create()
{
  Cube3D* ret = new Cube3D();
  ret->SetRenderer(MeshRenderer::Create(AssetManager::GetDefaultAsset<rcMesh>(DefaultUniqueID::MESH_CUBE)->CreateFromFile(), ret));
  ret->GetRenderer()->SetMaterial(AssetManager::GetDefaultAsset<rcMaterial>(DefaultUniqueID::MATERIAL_WHITE)->CreateFromFile());
  return ret;
}
