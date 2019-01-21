#pragma once

#include "Transform.h"
#include "Transform3DRotator.h"

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
  // Methods
  // =================================================================
public:
  void OnInit() override;

  //これらのカメラ操作関数は現在の位置、回転、スケールを基準にしたカメラ操作を行う
  void Move(const TVec3f& move);
  void Move(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  void MoveX(T_FLOAT x);
  void MoveY(T_FLOAT y);
  void MoveZ(T_FLOAT z);

  void LookAt(const TVec3f& target, const TVec3f& up = TVec3f::up);

protected:
  void UpdateTranslateMatrix(Matrix4x4* matrix) override;
  void UpdateScaleMatrix(Matrix4x4* matrix) override;
  void UpdateRotateMatrix(Matrix4x4* matrix) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  void SetPosition(const TVec3f& position);
  void SetPosition(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  GG_INLINE const TVec3f& GetPosition() const
  {
    return this->position_;
  }
  void SetX(T_FLOAT x);
  GG_INLINE T_FLOAT GetX() const
  {
    return this->position_.x;
  }
  void SetY(T_FLOAT y);
  GG_INLINE T_FLOAT GetY() const
  {
    return this->position_.y;
  }
  void SetZ(T_FLOAT z);
  GG_INLINE T_FLOAT GetZ() const
  {
    return this->position_.z;
  }

  void SetScale(const TVec3f& scale);
  void SetScale(T_FLOAT scale);
  void SetScale(T_FLOAT scale_x, T_FLOAT scale_y, T_FLOAT scale_z);
  GG_INLINE const TVec3f& GetScale() const
  {
    return this->scale_;
  }
  GG_INLINE T_FLOAT GetScaleMax() const
  {
    return this->scale_max_;
  }
  void SetScaleX(T_FLOAT scale_x);
  GG_INLINE T_FLOAT GetScaleX() const
  {
    return this->scale_.x;
  }
  void SetScaleY(T_FLOAT scale_y);
  GG_INLINE T_FLOAT GetScaleY() const
  {
    return this->scale_.y;
  }
  void SetScaleZ(T_FLOAT scale_z);
  GG_INLINE T_FLOAT GetScaleZ() const
  {
    return this->scale_.z;
  }

  // =================================================================
  // delegate to transform matrix
  // =================================================================
public:
  GG_INLINE const TVec3f GetDirection() const
  {
    return this->GetMatrix().GetDirection3d();
  }
  GG_INLINE const TVec3f GetWorldPosition() const
  {
    return this->GetWorldMatrix().GetPosition3d();
  }
  GG_INLINE const TVec3f GetWorldDirection() const
  {
    return this->GetWorldMatrix().GetDirection3d();
  }

  // =================================================================
  // delegate to Transform3DRotator
  // =================================================================
public:
  GG_INLINE void Rotate(const TVec3f& v, T_FLOAT rad)
  {
    this->rotator_->Rotate(v, rad);
  }
  GG_INLINE void RotateX(T_FLOAT rad)
  {
    this->rotator_->RotateX(rad);
  }
  GG_INLINE void RotateY(T_FLOAT rad)
  {
    this->rotator_->RotateY(rad);
  }
  GG_INLINE void RotateZ(T_FLOAT rad)
  {
    this->rotator_->RotateZ(rad);
  }

  GG_INLINE void LerpRotation(const Quaternion& a, const Quaternion& b, T_FLOAT t)
  {
    this->rotator_->Lerp(a, b, t);
  }
  GG_INLINE void LerpRotation(const Quaternion& b, T_FLOAT t)
  {
    this->rotator_->Lerp(b, t);
  }
  GG_INLINE void SlerpRotation(const Quaternion& a, const Quaternion& b, T_FLOAT t)
  {
    this->rotator_->Slerp(a, b, t);
  }
  GG_INLINE void SlerpRotation(const Quaternion& b, T_FLOAT t)
  {
    this->rotator_->Slerp(b, t);
  }

  GG_INLINE void SetEularAngles(const TVec3f& rotation)
  {
    this->rotator_->SetEularAngles(rotation);
  }
  GG_INLINE void SetEularAngles(T_FLOAT x, T_FLOAT y, T_FLOAT z)
  {
    this->rotator_->SetEularAngles(x, y, z);
  }
  GG_INLINE const TVec3f& GetEularAngles()
  {
    return this->rotator_->GetEularAngles();
  }

  GG_INLINE void SetEularX(T_FLOAT x)
  {
    this->rotator_->SetEularX(x);
  }
  GG_INLINE T_FLOAT GetEularX()
  {
    return this->rotator_->GetEularX();
  }

  GG_INLINE void SetEularY(T_FLOAT y)
  {
    this->rotator_->SetEularY(y);
  }
  GG_INLINE T_FLOAT GetEularY()
  {
    return this->rotator_->GetEularY();
  }

  GG_INLINE void SetEularZ(T_FLOAT z)
  {
    this->rotator_->SetEularZ(z);
  }
  GG_INLINE T_FLOAT GetEularZ()
  {
    return this->rotator_->GetEularZ();
  }

  GG_INLINE void SetQuaternion(const Quaternion& q)
  {
    return this->rotator_->SetQuaternion(q);
  }
  GG_INLINE const Quaternion& GetQuaternion() const
  {
    return this->rotator_->GetQuaternion();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject3D* entity_;

  TVec3f position_;
  TVec3f scale_;
  T_FLOAT scale_max_;
  Transform3DRotator* rotator_;
};