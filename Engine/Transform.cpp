#include "Transform.h"
#include "GameObject.h"

#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Transform::Transform(GameObject* entity)
  : entity_(entity)
{
  this->translate_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
  this->scale_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
  this->rotation_matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
  this->matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
}

Transform::~Transform()
{
  NativeMethod::Matrix().Matrix4x4_Delete(this->translate_matrix_);
  NativeMethod::Matrix().Matrix4x4_Delete(this->scale_matrix_);
  NativeMethod::Matrix().Matrix4x4_Delete(this->rotation_matrix_);
  NativeMethod::Matrix().Matrix4x4_Delete(this->matrix_);
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
    NativeMethod::Matrix().Matrix4x4_Init(this->translate_matrix_);
    this->UpdateTranslateMatrix(this->translate_matrix_);

    this->translation_dirty_ = false;
    matrix_dirty = true;
  }
  if (this->scale_dirty_)
  {
    NativeMethod::Matrix().Matrix4x4_Init(this->scale_matrix_);
    this->UpdateScaleMatrix(this->scale_matrix_);
    this->scale_dirty_ = false;
    matrix_dirty = true;
  }
  if (this->rotation_dirty_)
  {
    NativeMethod::Matrix().Matrix4x4_Init(this->rotation_matrix_);
    this->UpdateRotateMatrix(this->rotation_matrix_);
    this->rotation_dirty_ = false;
    matrix_dirty = true;
  }

  NativeMethod::Matrix().Matrix4x4_Init(this->matrix_);
  NativeMethod::Matrix().Matrix4x4_Multiply(this->matrix_, this->scale_matrix_);
  NativeMethod::Matrix().Matrix4x4_Multiply(this->matrix_, this->rotation_matrix_);
  NativeMethod::Matrix().Matrix4x4_Multiply(this->matrix_, this->translate_matrix_);

  this->OnUpdateMatrix(this->matrix_);
  return true;
}
