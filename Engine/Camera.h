#pragma once

#include "GameComponent.h"

#include "NativeType.h"
#include "RenderTexture.h"
#include "GameObjectRenderState.h"

#include "Geometry.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

class Scene;
class GameObject;

class Camera : public GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera();
  virtual ~Camera();

  // =================================================================
  // Method
  // =================================================================
public:
  void DrawScene(Scene* scene);

  virtual bool FrustumCulling(const TVec3f& positive, const TVec3f& negative, T_INT8* first_index = nullptr) const = 0;
  virtual const Matrix4x4& GetViewMatrix() const = 0;
  virtual const Matrix4x4& GetProjectionMatrix() const = 0;

protected:

  virtual void SetupCamera();

  virtual void OnViewportChanged() {}

  virtual void OnDrawScene(Scene* scene) = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  //ビューポート領域をクリアしてから描画するかのフラグ
  inline void SetViewportClear(bool clear)
  {
    this->viewport_clear_ = clear;
  }
  inline bool IsViewportClear() const
  {
    return this->viewport_clear_;
  }

  inline void SetTargetTexture(RenderTexture* texture)
  {
    this->target_texture_ = texture;
  }

  inline RenderTexture* GetTargetTexture() const
  {
    return this->target_texture_;
  }

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

  inline const TVec3f& GetDirection() const
  {
    return this->direction_;
  }

  inline GameObject* GetEntity()
  {
    return this->entity_;
  }
  inline const GameObject* GetEntity() const
  {
    return this->entity_;
  }

  inline GameObjectRenderState* GetRenderState()
  {
    return this->render_state_;
  }
  inline const GameObjectRenderState* GetRenderState() const
  {
    return this->render_state_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  GameObjectRenderState* render_state_;
  GameObject* entity_;
  TVec3f direction_;

private:
  RenderTexture* target_texture_;
  bool viewport_clear_;
  TVec2f position_;
  TSizef size_;
  T_FLOAT z_min_, z_max_;

};
