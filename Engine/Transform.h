#ifndef HAL_ENGINE_ENTITY_TRANSFORM_H_
#define HAL_ENGINE_ENTITY_TRANSFORM_H_

#include "NativeType.h"
#include "Matrix4x4.h"

class GameObject;

class Transform
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Transform(GameObject* entity);
  virtual ~Transform();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init();

protected:
  virtual void OnInit() = 0;

public:
  virtual void OnTransformChanged();
  virtual void OnScaleChanged();
  virtual void OnRotationChanged();

  void OnWorldTransformDirty();

protected:
  void UpdateMatrix();
  void UpdateWorldMatrix();

  virtual void UpdateTranslateMatrix(Matrix4x4* matrix) = 0;
  virtual void UpdateRotateMatrix(Matrix4x4* matrix) = 0;
  virtual void UpdateScaleMatrix(Matrix4x4* matrix) = 0;

  virtual const Matrix4x4& GetParentWorldMatrix() = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline const Matrix4x4& GetMatrix() const
  {
    const_cast<Transform*>(this)->UpdateMatrix();
    return this->matrix_;
  }

  inline const Matrix4x4& GetTranslateMatrix() const
  {
    const_cast<Transform*>(this)->UpdateMatrix();
    return this->translate_matrix_;
  }

  inline const Matrix4x4& GetRotationMatrix() const
  {
    const_cast<Transform*>(this)->UpdateMatrix();
    return this->rotation_matrix_;
  }

  inline const Matrix4x4& GetScaleMatrix() const
  {
    const_cast<Transform*>(this)->UpdateMatrix();
    return this->scale_matrix_;
  }

  inline const Matrix4x4& GetWorldMatrix() const
  {
    const_cast<Transform*>(this)->UpdateWorldMatrix();
    return this->world_matrix_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject* entity_;

  Matrix4x4 translate_matrix_;
  Matrix4x4 rotation_matrix_;
  Matrix4x4 scale_matrix_;
  Matrix4x4 matrix_;
  Matrix4x4 world_matrix_;

  bool translation_dirty_;
  bool rotation_dirty_;
  bool scale_dirty_;
  bool world_transform_dirty_;
};

#endif//HAL_ENGINE_ENTITY_TRANSFORM_H_
