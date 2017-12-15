#pragma once
#include "Transform.h"
#include "Quaternion.h"

class GameObject3D;

class Transform3D : public Transform
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Transform3D(GameObject3D* entity);
  ~Transform3D();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void OnInit() override;

  //これらのカメラ操作関数は現在の位置、回転、スケールを基準にしたカメラ操作を行う
  void Move(const TVec3f& move);
  void Move(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  void MoveX(T_FLOAT x);
  void MoveY(T_FLOAT y);
  void MoveZ(T_FLOAT z);

  void MoveCircular(const TVec3f& move, const TVec3f& pos);
  void MoveCircular(T_FLOAT x, T_FLOAT y, T_FLOAT z, const TVec3f& pos);
  //戻り値には移動後のposとの角度が返される
  T_FLOAT MoveCircularX(T_FLOAT x, const TVec3f& pos);
  T_FLOAT MoveCircularY(T_FLOAT y, const TVec3f& pos);
  T_FLOAT MoveCircularZ(T_FLOAT z, const TVec3f& pos);

  inline void RotationAxis(const TVec3f& rotation)
  {
    this->SetRotation(this->GetRotation() + rotation);
  }
  inline void RotationAxis(T_FLOAT x_axis, T_FLOAT y_axis, T_FLOAT z_axis)
  {
    this->SetRotation(
      this->GetRotationX() + x_axis,
      this->GetRotationY() + y_axis, 
      this->GetRotationZ() + z_axis
      );
  }
  void RotationXAxis(T_FLOAT x_axis)
  {
    this->SetRotationX(this->GetRotationX() + x_axis);
  }
  void RotationYAxis(T_FLOAT y_axis)
  {
    this->SetRotationY(this->GetRotationY() + y_axis);
  }
  void RotationZAxis(T_FLOAT z_axis)
  {
    this->SetRotationZ(this->GetRotationZ() + z_axis);
  }

  void RotationX(T_FLOAT x);
  void RotationY(T_FLOAT y);
  void RotationZ(T_FLOAT z);

  void OnRotationChanged() override;

  void UpdateWorldMatrix(LP_MATRIX_4x4 matrix);

protected:
  virtual void UpdateTranslateMatrix(LP_MATRIX_4x4 matrix) override;
  virtual void UpdateScaleMatrix(LP_MATRIX_4x4 matrix) override;
  virtual void UpdateRotateMatrix(LP_MATRIX_4x4 matrix) override;
  virtual void OnUpdateMatrix(LP_MATRIX_4x4 matrix) override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  const TVec3f& GetMatrixAppliedPosition();
  void ApplyMatrixToPosition(TVec3f* dest);

  const TVec3f& GetWorldPosition(GameObject3D* root = nullptr);
  T_FLOAT GetWorldX(GameObject3D* root = nullptr);
  T_FLOAT GetWorldY(GameObject3D* root = nullptr);
  T_FLOAT GetWorldZ(GameObject3D* root = nullptr);

  void SetPosition(const TVec3f& position);
  void SetPosition(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  inline const TVec3f& GetPosition() const
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
  void SetZ(T_FLOAT z);
  inline T_FLOAT GetZ() const
  {
    return this->position_.z;
  }

  void SetScale(const TVec3f& scale);
  void SetScale(T_FLOAT scale);
  void SetScale(T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z);
  inline const TVec3f& GetScale() const
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
  void SetScaleZ(T_FLOAT scale_z);
  inline T_FLOAT GetScaleZ() const
  {
    return this->scale_.z;
  }

  void SetRotation(const TVec3f& rotation);
  void SetRotation(T_FLOAT rotation_x, T_FLOAT rotation_y, T_FLOAT rotation_z);
  inline const TVec3f& GetRotation()
  {
    return this->rotation_;
//    return this->quaternion_.EularAngles();
  }
  void SetRotationX(T_FLOAT rotation_x);
  inline T_FLOAT GetRotationX()
  {
    return this->rotation_.x;
//    return this->quaternion_.EularAngles().x;
  }
  void SetRotationY(T_FLOAT rotation_y);
  inline T_FLOAT GetRotationY()
  {
    return this->rotation_.y;
//    return this->quaternion_.EularAngles().y;
  }
  void SetRotationZ(T_FLOAT rotation_z);
  inline T_FLOAT GetRotationZ()
  {
    return this->rotation_.z;
//    return this->quaternion_.EularAngles().z;
  }

  inline const TVec3f& GetDirection()
  {
    return this->direction_;
  }

  inline LP_MATRIX_4x4 GetWorldMatrix()
  {
    return this->world_matrix_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject3D* entity_;

  TVec3f direction_;

  TVec3f position_;
  TVec3f scale_;
  TVec3f rotation_;
//  Quaternion quaternion_;

  TVec3f world_position_;

  TVec3f matrix_applied_position_;

  LP_MATRIX_4x4 world_matrix_;
};