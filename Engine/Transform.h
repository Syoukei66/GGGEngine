#ifndef HAL_ENGINE_ENTITY_TRANSFORM_H_
#define HAL_ENGINE_ENTITY_TRANSFORM_H_

#include "NativeType.h"
#include "Geometry.h"

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

  virtual void UpdateTranslateMatrix(LP_MATRIX_4x4 matrix) = 0;
  virtual void UpdateRotateMatrix(LP_MATRIX_4x4 matrix) = 0;
  virtual void UpdateScaleMatrix(LP_MATRIX_4x4 matrix) = 0;
  virtual void OnUpdateMatrix(LP_MATRIX_4x4 matrix) = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:

  inline LP_MATRIX_4x4 GetMatrix()
  {
    this->UpdateMatrix();
    return this->matrix_;
  }

  inline LP_MATRIX_4x4 GetTranslateMatrix()
  {
    this->UpdateMatrix();
    return this->translate_matrix_;
  }

  inline LP_MATRIX_4x4 GetRotationMatrix()
  {
    this->UpdateMatrix();
    return this->rotation_matrix_;
  }

  inline LP_MATRIX_4x4 GetScaleMatrix()
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

  LP_MATRIX_4x4 translate_matrix_;
  LP_MATRIX_4x4 rotation_matrix_;
  LP_MATRIX_4x4 scale_matrix_;
  LP_MATRIX_4x4 matrix_;

  bool translation_dirty_;
  bool rotation_dirty_;
  bool scale_dirty_;
};

#endif//HAL_ENGINE_ENTITY_TRANSFORM_H_
