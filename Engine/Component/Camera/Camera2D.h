#pragma once

#include <Engine/GameObject/GameObject.h>

#include "Camera.h"

class Camera2D : public Camera
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_COMPONENT(Camera2D);
  GG_CREATE_FUNC_1(Camera2D, GameObject*, obj);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual bool FrustumCulling(const TVec3f& positive, const TVec3f& negative, T_INT8* first_index = nullptr) const override;

protected:
  virtual void UpdateViewMatrix() override;
  virtual void UpdateProjectionMatrix() override;

};