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
  //GameObjectに更新が必要な変更が行われた事を伝えるメソッドです。
  //全ての更新は描画メソッド内で行われます。
  virtual void OnTransformChanged();
  virtual void OnScaleChanged();
  virtual void OnRotationChanged();

  void OnWorldPositionDirty();

protected:
  
  bool UpdateMatrix();

  virtual void UpdateTranslateMatrix(INativeMatrix* matrix) = 0;
  virtual void UpdateRotateMatrix(INativeMatrix* matrix) = 0;
  virtual void UpdateScaleMatrix(INativeMatrix* matrix) = 0;
  virtual void OnUpdateMatrix(INativeMatrix* matrix) = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:

  inline INativeMatrix* GetMatrix()
  {
    this->UpdateMatrix();
    return this->matrix_;
  }

  inline INativeMatrix* GetTranslateMatrix()
  {
    this->UpdateMatrix();
    return this->translate_matrix_;
  }

  inline INativeMatrix* GetRotationMatrix()
  {
    this->UpdateMatrix();
    return this->rotation_matrix_;
  }

  inline INativeMatrix* GetScaleMatrix()
  {
    this->UpdateMatrix();
    return this->scale_matrix_;
  }


  // =================================================================
  // Data Member
  // =================================================================
protected:
  bool world_position_dirty_;

private:
  GameObject* entity_;

  INativeMatrix* translate_matrix_;
  INativeMatrix* rotation_matrix_;
  INativeMatrix* scale_matrix_;
  INativeMatrix* matrix_;

  bool translation_dirty_;
  bool rotation_dirty_;
  bool scale_dirty_;
};

#endif//HAL_ENGINE_ENTITY_TRANSFORM_H_
