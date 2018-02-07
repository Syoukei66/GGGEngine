#pragma once

#include <list>
#include "GameObjectRenderState.h"

class Camera2D;

class GameObject2DRenderState : public GameObjectRenderState
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject2DRenderState(Camera2D* camera);

};