#pragma once
//
//#include "Camera3D.h"
//
//class Camera3D_FirstPerson : public Camera3D
//{
//  // =================================================================
//  // Constructor / Destructor
//  // =================================================================
//public:
//  Camera3D_FirstPerson(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
//  Camera3D_FirstPerson();
//  virtual ~Camera3D_FirstPerson();
//
//  // =================================================================
//  // Methods for/from SuperClass/Interfaces
//  // =================================================================
//public:
//  virtual LP_MATRIX_4x4 GetViewMatrix() override;
//  void SetPlayer(GameObject3D* player);
//
//private:
//  GameObject3D* entity_;
//  TVec3f look_at_pos_;
//
//  LP_MATRIX_4x4 matrix_;
//  LP_MATRIX_4x4 inv_;
//
//};
