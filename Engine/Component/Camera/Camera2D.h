#pragma once

#include <Engine/GameObject/GameObject2D.h>

#include "Camera.h"

class Camera2D : public Camera
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_1(Camera2D, GameObject*);

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
    return SharedRef<GameObject2D>::StaticCast(this->GetObject())->GetTransform();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Matrix4x4 projection_matrix_;
  bool projection_dirty_;
};