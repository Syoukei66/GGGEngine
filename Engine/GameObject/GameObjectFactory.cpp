#include "GameObjectFactory.h"

#include <Asset/Sprite/Sprite.h>
#include <Asset/StaticModel/StaticModel.h>
#include <Asset/CharacterModel/CharacterModel.h>

#include <Engine/Component/Renderer/SpriteRenderer.h>
#include <Engine/Component/Renderer/MeshRenderer.h>

#include <Engine/GameObject/Transform/Transform.h>

SharedRef<GameObject> GameObjectFactory::Create(const SharedRef<rcSprite>& sprite)
{
  const SharedRef<GameObject>& ret = GameObject::Create();

  ret->AddComponent<SpriteRenderer>()->SetSprite(sprite);
  
  return ret;
}

SharedRef<GameObject> CreateNode(const SharedRef<rcCharacterModel>& model, const CharacterNodeData& node, const SharedRef<GameObject>& mesh_root)
{
  if (node.mesh_indices_.size() > 0)
  {
    // MeshÇÃì«Ç›çûÇ›
    const SharedRef<rcDynamicMesh>& mesh = rcDynamicMesh::Create();
    const SharedRef<GameObject>& mesh_obj = GameObject::Create(node.name_);
    const SharedRef<MeshRenderer>& mesh_renderer = mesh_obj->AddComponent<MeshRenderer>();
    const T_UINT32 submesh_count = (T_UINT32)node.mesh_indices_.size();
    for (T_UINT32 i = 0; i < submesh_count; ++i)
    {
      const T_UINT32 mesh_index = node.mesh_indices_[i];
      mesh->Append(model->GetMesh(mesh_index));
      mesh_renderer->SetSharedMaterial(model->GetMeshMaterial(mesh_index), i);
    }
    mesh->CommitChanges();
    mesh_renderer->SetMesh(mesh);
    mesh_root->AddChild(mesh_obj);
    return nullptr;
  }

  const SharedRef<GameObject>& ret = GameObject::Create(node.name_);

  ret->GetTransform()->SetPosition(node.position_);
  ret->GetTransform()->SetScale(node.scale_);
  ret->GetTransform()->SetEularAngles(node.rotation_);

  for (const CharacterNodeData& child : node.children_)
  {
    const SharedRef<GameObject>& child_object = CreateNode(model, child, mesh_root);
    if (child_object)
    {
      ret->AddChild(child_object);
    }
  }

  return ret;
}

SharedRef<GameObject> GameObjectFactory::Create(const SharedRef<rcCharacterModel>& model)
{
  const SharedRef<GameObject>& root = GameObject::Create(model->GetName());
  const SharedRef<GameObject>& mesh_root = GameObject::Create("MESH_ROOT");
  const SharedRef<GameObject>& root_bone = CreateNode(model, model->GetRootNode(), mesh_root);
  root->AddChild(mesh_root);
  root->AddChild(root_bone);
  return root;
}

SharedRef<GameObject> GameObjectFactory::Create(const SharedRef<rcStaticModel>& model)
{
  const SharedRef<GameObject>& ret = GameObject::Create();

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
