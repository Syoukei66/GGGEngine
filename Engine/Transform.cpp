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
}

Transform::~Transform()
{
  delete this->translate_matrix_;
  delete this->scale_matrix_;
  delete this->rotation_matrix_;
  delete this->matrix_;
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
  this->OnWorldPositionDirty();
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

void Transform::OnWorldPositionDirty()
{
  this->world_position_dirty_ = true;
}

bool Transform::UpdateMatrix()
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

  this->matrix_->Init();
  this->matrix_->Multiple(*this->scale_matrix_);
  this->matrix_->Multiple(*this->rotation_matrix_);
  this->matrix_->Multiple(*this->translate_matrix_);

  this->OnUpdateMatrix(this->matrix_);
  return true;
}
