#pragma once

#include <Engine/GameObject/GameObject2D.h>

#include "Camera.h"

class Camera2D : public Camera
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera2D(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera2D();
  virtual ~Camera2D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual bool FrustumCulling(const TVec3f& positive, const TVec3f& negative, T_INT8* first_index = nullptr) const override;

  virtual const Matrix4x4& GetViewMatrix() const override;
  virtual const Matrix4x4& GetProjectionMatrix() const override;

protected:
  virtual void OnViewportChanged() override;
  virtual void OnDrawScene(Scene* scene) override;

  // =================================================================
  // Methods
  // =================================================================
public:
  GG_INLINE GameObjectRenderState* GetRenderState()
  {
    return this->render_state_;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE Transform2D* GetTransform()
  {
    return ((GameObject2D*)this->entity_)->GetTransform();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Matrix4x4 projection_matrix_;
  bool projection_dirty_;
};