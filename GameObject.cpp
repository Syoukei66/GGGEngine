#include "GameObject.h"
#include <stdlib.h>

#include "EngineInitializeSetting.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject::GameObject()
  : visible_(true)
  , layer_id_(EngineInitializeSetting::GetInstance().GetDefaultLayerId())
  , blend_function_src_(BlendFunction::BLEND_DEFAULT_SRC)
  , blend_function_dst_(BlendFunction::BLEND_DEFAULT_DST)
{}

GameObject::~GameObject()
{}

// =================================================================
// Method
// =================================================================
void GameObject::Init()
{
  this->visible_ = true;
  this->blend_function_src_ = BlendFunction::BLEND_DEFAULT_SRC;
  this->blend_function_dst_ = BlendFunction::BLEND_DEFAULT_DST;
}

void GameObject::ApplyBlendMode(GameObjectRenderState* state)
{
  state->SetBlendMode(this->blend_function_src_, this->blend_function_dst_);
}
