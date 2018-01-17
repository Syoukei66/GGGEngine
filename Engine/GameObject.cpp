#include "GameObject.h"
#include <stdlib.h>

#include "EngineInitializeSetting.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject::GameObject()
  : visible_(true)
  , layer_id_(EngineInitializeSetting::GetInstance().GetDefaultLayerId())
{
  this->material_ = new Material();
}

GameObject::~GameObject()
{
  delete this->material_;
}

// =================================================================
// Method
// =================================================================
void GameObject::Init()
{
  this->visible_ = true;
}
