#include "Cube3D.h"
#include "MeshRenderer.h"
#include "EngineAsset.h"

// =================================================================
// Factory Method
// =================================================================
Cube3D* Cube3D::Create()
{
  Cube3D* ret = new Cube3D();
  ret->SetRenderer(MeshRenderer::Create(EngineAsset::Mesh::CUBE.GetContents(), ret));
  ret->GetRenderer()->SetMaterial(EngineAsset::Material::LAMBERT);
  return ret;
}
