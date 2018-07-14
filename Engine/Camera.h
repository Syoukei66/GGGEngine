#pragma once

#include "GameComponent.h"

#include "RenderTexture.h"
#include "RenderState.h"

#include "Matrix4x4.h"
#include "Vector3.h"

class Camera : public GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera(GameObject* entity);
  virtual ~Camera();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void SetupCamera();
  virtual const Matrix4x4& GetViewMatrix() const = 0;
  virtual const Matrix4x4& GetProjectionMatrix() const = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  const TVec3f Get2dPositionScale(const GameObject* obj) const;
  const TVec3f Get2dPosition(const GameObject* obj) const;
  const TVec3f GetRayVector(const TVec2f& screen_position);


  inline void SetTargetTexture(RenderTexture* texture)
  {
    this->target_texture_ = texture;
  }
  inline RenderTexture* GetTargetTexture() const
  {
    return this->target_texture_;
  }

  inline RenderState* GetRenderState()
  {
    return this->render_state_;
  }
  inline const RenderState* GetRenderState() const
  {
    return this->render_state_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  RenderState* render_state_;

private:
  RenderTexture* target_texture_;

};
