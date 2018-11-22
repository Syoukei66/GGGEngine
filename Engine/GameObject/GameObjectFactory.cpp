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
SharedRef<GameObject2D> GameObjectFactory::Create(const SharedRef<rcSprite>& sprite)
{
  SharedRef<GameObject2D> ret = GameObject2D::Create();

  ret->AddComponent<SpriteRenderer>()->SetSprite(sprite);
  
  return ret;
}

// =================================================================
// GameObject3D
// =================================================================
SharedRef<GameObject3D> CreateNode(const SharedRef<rcCharacterModel>& model, const CharacterNodeData& node, const SharedRef<GameObject3D>& mesh_root)
{
  SharedRef<GameObject3D> ret = GameObject3D::Create();

  // MeshÇÃì«Ç›çûÇ›
  for (T_FIXED_UINT32 index : node.mesh_indices_)
  {
    SharedRef<GameObject3D> mesh_obj = GameObject3D::Create();
    const SharedRef<const rcDynamicMesh>& mesh = model->GetMesh(index);
    const SharedRef<const rcMaterial>& material = model->GetMeshMaterial(index);
    const SharedRef<MeshRenderer>& mesh_renderer = mesh_obj->AddComponent<MeshRenderer>();
    mesh_renderer->SetMesh(mesh);
    mesh_renderer->SetSharedMaterial(material);
    mesh_root->AddChild(mesh_obj);
  }

  ret->GetTransform()->SetPosition(node.position_);
  ret->GetTransform()->SetScale(node.scale_);
  ret->GetTransform()->SetEularAngles(node.rotation_);

  for (const CharacterNodeData& child : node.children_)
  {
    SharedRef<GameObject3D> child_object = CreateNode(model, child, mesh_root);
    ret->AddChild(child_object);
  }

  return ret;
}

UniqueRef<GameObject3D> GameObjectFactory::Create(const SharedRef<rcCharacterModel>& model)
{
  UniqueRef<GameObject3D> root = GameObject3D::Create();
  SharedRef<GameObject3D> mesh_root = GameObject3D::Create();
  SharedRef<GameObject3D> root_bone = CreateNode(model, model->GetRootNode(), mesh_root);
  root->AddChild(mesh_root);
  root->AddChild(root_bone);
  return root;
}

SharedRef<GameObject3D> GameObjectFactory::Create(const SharedRef<rcStaticModel>& model)
{
  SharedRef<GameObject3D> ret = GameObject3D::Create();

  const SharedRef<const rcMesh>& mesh = model->GetMesh();
  const SharedRef<MeshRenderer>& mesh_renderer = ret->AddComponent<MeshRenderer>();
  mesh_renderer->SetMesh(mesh);
  const T_UINT8 submesh_count = mesh->GetSubmeshCount();
  for (T_UINT8 i = 0; i < submesh_count; ++i)
  {
    mesh_renderer->SetSharedMaterial(model->GetMaterial(i), i);
  }

  return ret;
}
