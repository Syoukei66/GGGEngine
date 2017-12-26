#pragma once

#include "NativeType.h"
#include "Geometry.h"
#include "GameComponent.h"
#include "NativeMatrix.h"

class Scene;

class Camera : public GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void DrawScene(Scene* scene) = 0;

  virtual const INativeMatrix* GetViewMatrix() = 0;
  virtual const INativeMatrix* GetProjectionMatrix() = 0;

protected:
  void SetupCamera();
  void CheckViewportDirty();
  virtual void OnViewportDirty() = 0;

private:
  inline void OnViewportChanged()
  {
    this->viewport_dirty_ = true;
  }

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetViewportPosition(const TVec2f& position);
  void SetViewportPosition(T_FLOAT x, T_FLOAT y);
  inline const TVec2f& GetViewportPosition() const
  {
    return this->position_;
  }

  void SetViewportX(T_FLOAT x);
  inline T_FLOAT GetViewportX() const
  {
    return this->position_.x;
  }

  void SetViewportY(T_FLOAT y);
  inline T_FLOAT GetViewportY() const
  {
    return this->position_.y;
  } 

  void SetViewportSize(const TSizef& size);
  void SetViewportSize(T_FLOAT width, T_FLOAT height);
  inline const TSizef& GetViewportSize() const
  {
    return this->size_;
  }

  void SetViewportWidth(T_FLOAT width);
  inline T_FLOAT GetViewportWidth() const
  {
    return this->size_.width;
  }

  void SetViewportHeight(T_FLOAT height);
  inline T_FLOAT GetViewportHeight() const
  {
    return this->size_.height;
  }

  void SetViewportZRange(T_FLOAT z_min, T_FLOAT z_max);
  void SetViewportZMin(T_FLOAT z_min);
  inline T_FLOAT GetViewportZMin()
  {
    return this->z_min_;
  }

  void SetViewportZMax(T_FLOAT z_max);
  inline T_FLOAT GetViewportZMax()
  {
    return this->z_max_;
  }


  // =================================================================
  // Data Member
  // =================================================================
private:

  TVec2f position_;
  TSizef size_;
  T_FLOAT z_min_, z_max_;
  bool viewport_dirty_;

};
