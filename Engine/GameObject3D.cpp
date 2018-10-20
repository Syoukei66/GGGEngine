#include "GameObject3D.h"
#include "GameObjectRenderState.h"

#include <Core/Model.h>

#include "MeshRenderer.h"

// =================================================================
// Factory Method
// =================================================================
GameObject3D* GameObject3D::Create(const SharedRef<const rcModel>& model)
{
  GameObject3D* ret = new GameObject3D();

  MeshRenderer* mesh_renderer = MeshRenderer::Create(model->GetMesh(), ret);
  const T_UINT8 submesh_count = model->GetSubmeshCount();
  for (T_UINT8 i = 0; i < submesh_count; ++i)
  {
    mesh_renderer->SetSharedMaterial(model->GetMaterial(i), i);
  }

  ret->SetRenderer(mesh_renderer);

  return ret;
}

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject3D::GameObject3D()
  : parent_(nullptr)
  , children_()
{
  this->transform_ = new Transform3D(this);
  this->transform_->Init();
}

GameObject3D::~GameObject3D()
{
  delete this->transform_;
}

// =================================================================
// Method
// =================================================================
void GameObject3D::Init()
{
  GameObject::Init();
}

void GameObject3D::AddChild(GameObject3D* child)
{
  child->parent_ = this;
  this->children_.emplace_back(child);
  child->FireOnPositionChanged(this);
  child->FireOnScaleChanged(this);
  child->FireOnRotationChanged(this);
}

void GameObject3D::RemoveChild(GameObject3D* child)
{
  if (child->parent_ != this)
  {
    return;
  }
  child->parent_ = nullptr;
  for (std::vector<GameObject3D*>::iterator it = this->children_.begin(); it != this->children_.end(); ++it)
  {
    if (child == (*it))
    {
      this->children_.erase(it);
      return;
    }
  }
}

void GameObject3D::RemoveSelf()
{
  if (!this->parent_)
  {
    return;
  }
  this->parent_->RemoveChild(this);
}

void GameObject3D::ClearChildren()
{
  for (GameObject3D* child : this->children_)
  {
    child->parent_ = nullptr;
  }
  this->children_.clear();
}

// =================================================================
// Events
// =================================================================
void GameObject3D::ManagedDraw(GameObjectRenderState* state)
{
  if (!this->IsVisible())
  {
    return;
  }

  // 自分自身の描画
  this->Draw(state);

  // 子の描画
  for (GameObject3D* child : this->children_)
  {
    child->ManagedDraw(state);
  }
}

void GameObject3D::ManagedPreUpdate()
{
  this->PreUpdate();
  for (GameObject3D* child : this->children_)
  {
    child->ManagedPreUpdate();
  }
}

void GameObject3D::ManagedUpdate()
{
  this->Update();
  for (GameObject3D* child : this->children_)
  {
    child->ManagedUpdate();
  }
}

void GameObject3D::ManagedPostUpdate()
{
  this->PostUpdate();
  for (GameObject3D* child : this->children_)
  {
    child->ManagedPostUpdate();
  }
}

void GameObject3D::FireOnPositionChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnPositionChanged(root);
  for (GameObject3D* child : this->children_)
  {
    child->FireOnPositionChanged(root);
  }
}

void GameObject3D::FireOnScaleChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnScaleChanged(root);
  for (GameObject3D* child : this->children_)
  {
    child->FireOnScaleChanged(root);
  }
}

void GameObject3D::FireOnRotationChanged(GameObject* root)
{
  this->transform_->OnWorldTransformDirty();
  this->OnRotationChanged(root);
  for (GameObject3D* child : this->children_)
  {
    child->FireOnRotationChanged(root);
  }
}