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

  void UpdateWorldMatrix(NativeMatrixInstance* native_instance);

protected:
  virtual void UpdateTranslateMatrix(INativeMatrix* matrix) override;
  virtual void UpdateScaleMatrix(INativeMatrix* matrix) override;
  virtual void UpdateRotateMatrix(INativeMatrix* matrix) override;
  virtual void OnUpdateMatrix(INativeMatrix* matrix) override;

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

  inline const TVec3f& GetDirection()
  {
    return this->direction_;
  }

  inline INativeMatrix* GetWorldMatrix()
  {
    return this->world_matrix_;
  }

  inline Transform3DRotator* GetRotator()
  {
    return this->rotator_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject3D* entity_;

  TVec3f direction_;

  TVec3f position_;
  TVec3f scale_;
  Transform3DRotator* rotator_;

  TVec3f world_position_;

  TVec3f matrix_applied_position_;

  INativeMatrix* world_matrix_;
};