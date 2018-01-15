#ifndef HAL_ENGINE_ENTITY_TRANSFORM_H_
#define HAL_ENGINE_ENTITY_TRANSFORM_H_

#include "NativeType.h"
#include "Geometry.h"
#include "NativeMatrix.h"

class GameObject;

class Transform
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Transform(GameObject* entity);
  ~Transform();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init();

protected:
  virtual void OnInit() = 0;

public:
  //GameObject�ɍX�V���K�v�ȕύX���s��ꂽ����`���郁�\�b�h�ł��B
  //�S�Ă̍X�V�͕`�惁�\�b�h���ōs���܂��B
  virtual void OnTransformChanged();
  virtual void OnScaleChanged();
  virtual void OnRotationChanged();

  void OnWorldTransformDirty();

protected:
  void UpdateMatrix();
  void UpdateWorldMatrix();

  virtual void UpdateTranslateMatrix(INativeMatrix* matrix) = 0;
  virtual void UpdateRotateMatrix(INativeMatrix* matrix) = 0;
  virtual void UpdateScaleMatrix(INativeMatrix* matrix) = 0;

  virtual INativeMatrix* GetParentWorldMatrix() = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  //TODO: Matrix�𒼐ڕҏW�ł��Ȃ��悤�ɂ���K�v������̂ł�
  inline INativeMatrix* GetMatrix() const
  {
    const_cast<Transform*>(this)->UpdateMatrix();
    return this->matrix_;
  }

  inline INativeMatrix* GetTranslateMatrix() const
  {
    const_cast<Transform*>(this)->UpdateMatrix();
    return this->translate_matrix_;
  }

  inline INativeMatrix* GetRotationMatrix() const
  {
    const_cast<Transform*>(this)->UpdateMatrix();
    return this->rotation_matrix_;
  }

  inline INativeMatrix* GetScaleMatrix() const
  {
    const_cast<Transform*>(this)->UpdateMatrix();
    return this->scale_matrix_;
  }

  inline INativeMatrix* GetWorldMatrix() const
  {
    const_cast<Transform*>(this)->UpdateWorldMatrix();
    return this->world_matrix_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject* entity_;

  INativeMatrix* translate_matrix_;
  INativeMatrix* rotation_matrix_;
  INativeMatrix* scale_matrix_;
  INativeMatrix* matrix_;
  INativeMatrix* world_matrix_;

  bool translation_dirty_;
  bool rotation_dirty_;
  bool scale_dirty_;
  bool world_transform_dirty_;
};

#endif//HAL_ENGINE_ENTITY_TRANSFORM_H_
