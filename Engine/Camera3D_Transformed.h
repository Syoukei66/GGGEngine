#pragma once

#include "Camera3D.h"
#include "GameObject3D.h"

//TODO: ビュー行列を編集するように変更すること
class Camera3D_Transformed : public Camera3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera3D_Transformed(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera3D_Transformed();
  virtual ~Camera3D_Transformed();
  
  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  //virtual void DrawLayers(Scene* scene, GameObject3DRenderState* state) override;

private:
  void UpdateMatrixes();

  // =================================================================
  // Methods
  // =================================================================
public:
  //これらのカメラ操作関数は現在の位置、回転、スケールを基準にしたカメラ操作を行う
  void Move(TVec3f value);
  void Move(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  void MoveX(T_FLOAT x);
  void MoveY(T_FLOAT y);
  void MoveZ(T_FLOAT z);
  void Rotation(TVec3f rotation);
  void Rotation(T_FLOAT x_axis, T_FLOAT y_axis, T_FLOAT z_axis);
  void RotationXAxis(T_FLOAT x_axis);
  void RotationYAxis(T_FLOAT y_axis);
  void RotationZAxis(T_FLOAT z_axis);

public:
  inline Transform3D* GetTransform()
  {
    return this->entity_->GetTransform();
  }

  inline const Transform3D* GetTransform() const
  {
    return this->entity_->GetTransform();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject3D* entity_;
  LP_MATRIX_4x4 inv_;
};
