#include "GameObject.h"
#include <stdlib.h>

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
// Methods
// =================================================================
void GameObject::Init()
{
  this->visible_ = true;
}

void GameObject::Draw(GameObjectRenderState* state)
{
  if (!this->renderer_)
  {
    return;
  }
  this->renderer_->ReserveDraw(state);
}
