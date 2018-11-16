#include "GameObjectFactory.h"

#include <Asset/Sprite/Sprite.h>
#include <Asset/StaticModel/StaticModel.h>
#include <Asset/CharacterModel/CharacterModel.h>

#include <Engine/Component/Renderer/SpriteRenderer.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

#include <Engine/GameObject/Transform/Transform3D.h>

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
GameObject3D* GameObjectFactory::Create(const SharedRef<rcCharacterModel>& model, const CharacterNodeData& node)
{
  GameObject3D* ret = new GameObject3D();

  const SharedRef<const rcMesh>& mesh = model->GetMesh(node.mesh_index_);
  MeshRenderer* mesh_renderer = MeshRenderer::Create(mesh, ret);
  const T_UINT8 submesh_count = mesh->GetSubmeshCount();
  for (T_UINT8 i = 0; i < submesh_count; ++i)
  {
    mesh_renderer->SetSharedMaterial(model->GetMaterial(i), i);
  }
  ret->SetRenderer(mesh_renderer);

  ret->GetTransform()->SetPosition(node.position_);
  ret->GetTransform()->SetScale(node.scale_);
  ret->GetTransform()->SetEularAngles(node.rotation_);

  for (const CharacterNodeData& child : node.children_)
  {
    GameObject3D* child_object = Create(model, child);
    ret->AddChild(child_object);
  }

  return ret;
}

GameObject3D* GameObjectFactory::Create(const SharedRef<rcCharacterModel>& model)
{
  return Create(model, model->GetRootNode());
}

GameObject3D* GameObjectFactory::Create(const SharedRef<rcStaticModel>& model)
{
  GameObject3D* ret = new GameObject3D();

  const SharedRef<const rcMesh>& mesh = model->GetMesh();
  MeshRenderer* mesh_renderer = MeshRenderer::Create(mesh, ret);
  const T_UINT8 submesh_count = mesh->GetSubmeshCount();
  for (T_UINT8 i = 0; i < submesh_count; ++i)
  {
    mesh_renderer->SetSharedMaterial(model->GetMaterial(i), i);
  }
  ret->SetRenderer(mesh_renderer);

  return ret;
}
