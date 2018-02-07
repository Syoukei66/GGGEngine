#include "GameObject.h"
#include <stdlib.h>

#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject::GameObject()
  : visible_(true)
  , renderer_(nullptr)
{
}

GameObject::~GameObject()
{
  delete this->renderer_;
}

// =================================================================
// Method
// =================================================================
void GameObject::Init()
{
  this->visible_ = true;
}

void GameObject::ManagedDraw(GameObjectRenderState* state)
{
  if (!this->renderer_)
  {
    return;
  }
  this->renderer_->ReserveDraw(state);
}
