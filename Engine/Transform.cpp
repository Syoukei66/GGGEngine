#include "Transform.h"
#include "GameObject.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Transform::Transform(GameObject* entity)
  : entity_(entity)
{
  this->translate_matrix_ = INativeMatrix::Create();
  this->scale_matrix_ = INativeMatrix::Create();
  this->rotation_matrix_ = INativeMatrix::Create();
  this->matrix_ = INativeMatrix::Create();
  this->world_matrix_ = INativeMatrix::Create();
}

Transform::~Transform()
{
  delete this->translate_matrix_;
  delete this->scale_matrix_;
  delete this->rotation_matrix_;
  delete this->matrix_;
  delete this->world_matrix_;
}

// =================================================================
// Method
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
  this->entity_->FireOnPositionChanged(this->entity_);
  this->translation_dirty_ = true;
}

void Transform::OnScaleChanged()
{
  this->entity_->FireOnScaleChanged(this->entity_);
  this->scale_dirty_ = true;
}

void Transform::OnRotationChanged()
{
  this->entity_->FireOnRotationChanged(this->entity_);
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
    this->translate_matrix_->Init();
    this->UpdateTranslateMatrix(this->translate_matrix_);
    this->translation_dirty_ = false;
    matrix_dirty = true;
  }
  if (this->scale_dirty_)
  {
    this->scale_matrix_->Init();
    this->UpdateScaleMatrix(this->scale_matrix_);
    this->scale_dirty_ = false;
    matrix_dirty = true;
  }
  if (this->rotation_dirty_)
  {
    this->rotation_matrix_->Init();
    this->UpdateRotateMatrix(this->rotation_matrix_);
    this->rotation_dirty_ = false;
    matrix_dirty = true;
  }
  if (matrix_dirty)
  {
    this->matrix_->Init();
    this->matrix_->Multiple(*this->scale_matrix_);
    this->matrix_->Multiple(*this->rotation_matrix_);
    this->matrix_->Multiple(*this->translate_matrix_);
  }
}

void Transform::UpdateWorldMatrix()
{
  if (!this->world_transform_dirty_)
  {
    return;
  }
  this->world_matrix_->Init();
  INativeMatrix* parent_world_matrix = this->GetParentWorldMatrix();
  if (parent_world_matrix)
  {
    this->world_matrix_->Multiple(*parent_world_matrix);
  }
  this->world_matrix_->Multiple(*this->GetMatrix());
  this->world_transform_dirty_ = false;
}
