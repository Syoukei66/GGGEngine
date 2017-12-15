#pragma once

#include "Transform.h"

class GameObject2D;

class Transform2D : public Transform
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Transform2D(GameObject2D* entity);
  ~Transform2D();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void OnInit() override;

  //これらのカメラ操作関数は現在の位置、回転、スケールを基準にしたカメラ操作を行う
  void Move(TVec2f value);
  void Move(T_FLOAT x, T_FLOAT y);
  void MoveX(T_FLOAT x);
  void MoveY(T_FLOAT y);
  void Rotation(TVec3f rotation);
  void Rotation(T_FLOAT x_axis, T_FLOAT y_axis);
  void RotationXAxis(T_FLOAT x_axis);
  void RotationYAxis(T_FLOAT y_axis);

protected:
  virtual void UpdateTranslateMatrix(LP_MATRIX_4x4 matrix);
  virtual void UpdateScaleMatrix(LP_MATRIX_4x4 matrix);
  virtual void UpdateRotateMatrix(LP_MATRIX_4x4 matrix);
  virtual void OnUpdateMatrix(LP_MATRIX_4x4 matrix);

  // =================================================================
  // setter/getter
  // =================================================================
public:
  TVec2f GetMatrixAppliedPosition();
  void ApplyMatrixToPosition(TVec2f* dest);

  const TVec2f& GetWorldPosition(GameObject2D* root = nullptr);
  T_FLOAT GetWorldX(GameObject2D* root = nullptr);
  T_FLOAT GetWorldY(GameObject2D* root = nullptr);

  void SetPositon(const TVec2f& position);
  void SetPositon(T_FLOAT x, T_FLOAT y);
  inline const TVec2f& GetPosition() const
  {
    return this->position_;
  }

  void SetX(T_FLOAT x);
  inline T_FLOAT GetX() const
  {
    return this->position_.x;
  }

  void SetY(T_FLOAT y);
  inline T_FLOAT GetY() const
  {
    return this->position_.y;
  }

  void SetScale(const TVec2f& scale);
  void SetScale(T_FLOAT scale);
  void SetScale(T_FLOAT scale_x, T_FLOAT scale_y);
  inline const TVec2f& GetScale() const
  {
    return this->scale_;
  }

  void SetScaleX(T_FLOAT scale_x);
  inline T_FLOAT GetScaleX() const
  {
    return this->scale_.x;
  }

  void SetScaleY(T_FLOAT scale_y);
  inline T_FLOAT GetScaleY() const
  {
    return this->scale_.y;
  }

  void SetRotation(T_FLOAT rotation);
  inline T_FLOAT GetRotation() const
  {
    return this->rotation_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject2D* entity_;

  TVec2f position_;
  TVec2f scale_;
  T_FLOAT rotation_;

  TVec2f world_position_;

  TVec2f matrix_applied_position_;
};