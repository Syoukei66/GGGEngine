#pragma once

#include "Camera3D.h"
#include "GameObject3D.h"

//TODO: �r���[�s���ҏW����悤�ɕύX���邱��
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
  // Methods
  // =================================================================
public:
  //�����̃J��������֐��͌��݂̈ʒu�A��]�A�X�P�[������ɂ����J����������s��
  void Move(TVec3f value);
  void Move(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  void MoveX(T_FLOAT x);
  void MoveY(T_FLOAT y);
  void MoveZ(T_FLOAT z);

  void RotateXAxis(T_FLOAT x_axis);
  void RotateYAxis(T_FLOAT y_axis);
  void RotateZAxis(T_FLOAT z_axis);

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
