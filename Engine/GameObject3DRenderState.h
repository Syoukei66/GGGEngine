#pragma once

#include <vector>
#include <map>
#include "GameObjectRenderState.h"

class GameObject3DRenderState : public GameObjectRenderState
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject3DRenderState(Camera* camera);
  ~GameObject3DRenderState();
  
};