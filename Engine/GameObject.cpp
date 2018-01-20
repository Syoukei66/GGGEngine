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
{
}

GameObject::~GameObject()
{
}

// =================================================================
// Method
// =================================================================
void GameObject::Init()
{
  this->visible_ = true;
}

void GameObject::UniqueMaterial()
{
  this->material_ = this->material_->InitialClone();
}
