#include "GameObject.h"
#include <stdlib.h>

#include "EngineInitializeSetting.h"
#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject::GameObject()
  : visible_(true)
  , layer_id_(EngineInitializeSetting::GetInstance().GetDefaultLayerId())
  , material_(nullptr)
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
  this->renderer_->Draw(state);
}

void GameObject::UniqueMaterial()
{
  this->material_ = this->material_->InitialClone();
}
