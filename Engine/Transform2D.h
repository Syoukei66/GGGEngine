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
  void OnInit() override;

protected:
  void UpdateTranslateMatrix(INativeMatrix* matrix) override;
  void UpdateScaleMatrix(INativeMatrix* matrix) override;
  void UpdateRotateMatrix(INativeMatrix* matrix) override;

  const INativeMatrix* GetParentWorldMatrix() override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
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
  // delegate to transform matrix
  // =================================================================
public:
  inline const TVec2f GetDirection() const
  {
    return this->GetMatrix().GetDirection2d();
  }
  inline const TVec2f GetWorldPosition() const
  {
    return this->GetWorldMatrix().GetPosition2d();
  }
  inline const TVec2f GetWorldDirection() const
  {
    return this->GetWorldMatrix().GetDirection2d();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject2D* entity_;

  TVec2f position_;
  TVec2f scale_;
  T_FLOAT rotation_;
};