#include "Transform.h"

#include <Engine/GameObject/GameObject.h>

// =================================================================
// Constructor / Destructor
// =================================================================
Transform::Transform(GameObject* entity)
  : entity_(entity)
  , translate_matrix_()
  , scale_matrix_()
  , rotation_matrix_()
  , matrix_()
  , world_matrix_()
{
}

Transform::~Transform()
{
}

// =================================================================
// Methods
// =================================================================
void Transform::Init()
{
  this->OnInit();
  this->OnTransformChanged();
  this->OnScaleChanged();
  this->OnRotationChanged();
  this->OnWorldTransformDirty();
}

void Transform::OnTransformChanged()
{
  this->entity_->FireOnPositionChanged();
  this->translation_dirty_ = true;
}

void Transform::OnScaleChanged()
{
  this->entity_->FireOnScaleChanged();
  this->scale_dirty_ = true;
}

void Transform::OnRotationChanged()
{
  this->entity_->FireOnRotationChanged();
  this->rotation_dirty_ = true;
}

void Transform::OnWorldTransformDirty()
{
  this->world_transform_dirty_ = true;
}

void Transform::UpdateMatrix()
{
  bool matrix_dirty = false;
  if (this->translation_dirty_)
  {
    this->translate_matrix_ = Matrix4x4::identity;
    this->UpdateTranslateMatrix(&this->translate_matrix_);
    this->translation_dirty_ = false;
    matrix_dirty = true;
  }
  if (this->scale_dirty_)
  {
    this->scale_matrix_ = Matrix4x4::identity;
    this->UpdateScaleMatrix(&this->scale_matrix_);
    this->scale_dirty_ = false;
    matrix_dirty = true;
  }
  if (this->rotation_dirty_)
  {
    this->rotation_matrix_ = Matrix4x4::identity;
    this->UpdateRotateMatrix(&this->rotation_matrix_);
    this->rotation_dirty_ = false;
    matrix_dirty = true;
  }
  if (matrix_dirty)
  {
    this->matrix_ = Matrix4x4::identity;
    this->matrix_ *= this->scale_matrix_;
    this->matrix_ *= this->rotation_matrix_;
    this->matrix_ *= this->translate_matrix_;
  }
}

void Transform::UpdateWorldMatrix()
{
  if (!this->world_transform_dirty_)
  {
    return;
  }
  this->world_matrix_ = this->GetMatrix();
  const Matrix4x4& parent_world_matrix = this->GetParentWorldMatrix();
  if (parent_world_matrix)
  {
    this->world_matrix_ *= parent_world_matrix;
  }
  this->world_transform_dirty_ = false;
}
