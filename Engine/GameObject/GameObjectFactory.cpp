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
GameObject3D* CreateNode(const SharedRef<rcCharacterModel>& model, const CharacterNodeData& node, GameObject3D* mesh_root)
{
  GameObject3D* ret = new GameObject3D();

  // MeshÇÃì«Ç›çûÇ›
  for (T_FIXED_UINT32 index : node.mesh_indices_)
  {
    GameObject3D* mesh_obj = new GameObject3D();
    const SharedRef<const rcMesh>& mesh = model->GetMesh(index);
    const SharedRef<const rcMaterial>& material = model->GetMeshMaterial(index);
    MeshRenderer* mesh_renderer = MeshRenderer::Create(mesh, ret);
    mesh_renderer->SetSharedMaterial(material);
    mesh_obj->SetRenderer(mesh_renderer);
    mesh_root->AddChild(mesh_obj);
  }

  ret->GetTransform()->SetPosition(node.position_);
  ret->GetTransform()->SetScale(node.scale_);
  ret->GetTransform()->SetEularAngles(node.rotation_);

  for (const CharacterNodeData& child : node.children_)
  {
    GameObject3D* child_object = CreateNode(model, child, mesh_root);
    ret->AddChild(child_object);
  }

  return ret;
}

GameObject3D* GameObjectFactory::Create(const SharedRef<rcCharacterModel>& model)
{
  GameObject3D* root = new GameObject3D();
  GameObject3D* mesh_root = new GameObject3D();
  GameObject3D* root_bone = CreateNode(model, model->GetRootNode(), mesh_root);
  root->AddChild(mesh_root);
  root->AddChild(root_bone);
  return root;
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
