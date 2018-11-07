#include "GameObjectFactory.h"

#include <Asset/Sprite/Sprite.h>
#include <Asset/Model/Model.h>

#include <Engine/Component/Renderer/SpriteRenderer.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

// =================================================================
// GameObject2D
// =================================================================
GameObject2D* GameObjectFactory::Create(const SharedRef<rcSprite>& sprite)
{
  GameObject2D* ret = new GameObject2D();

  ret->SetRenderer(SpriteRenderer::Create(sprite, ret));

  return ret;
}

// =================================================================
// GameObject3D
// =================================================================
GameObject3D* GameObjectFactory::Create(const SharedRef<rcModel>& model)
{
  GameObject3D* ret = new GameObject3D();

  MeshRenderer* mesh_renderer = MeshRenderer::Create(model->GetMesh(), ret);
  const T_UINT8 submesh_count = model->GetMesh()->GetSubmeshCount();
  for (T_UINT8 i = 0; i < submesh_count; ++i)
  {
    mesh_renderer->SetSharedMaterial(model->GetMaterial(i), i);
  }

  ret->SetRenderer(mesh_renderer);

  return ret;
}
