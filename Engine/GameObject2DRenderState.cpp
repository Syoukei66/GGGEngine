#include "GameObject2DRenderState.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObject2DRenderState::GameObject2DRenderState(Camera2D* camera)
  : camera_(camera)
{
}

GameObject2DRenderState::~GameObject2DRenderState()
{
}

// =================================================================
// Method
// =================================================================
void GameObject2DRenderState::Init()
{
  GameObjectRenderState::Init();
  this->world_color_ = Color::WHITE;
  this->color_stack_.clear();
}

void GameObject2DRenderState::PushColor(const Color& color)
{
  this->color_stack_.push_back(color);
}

void GameObject2DRenderState::PopColor()
{
  this->color_stack_.pop_back();
}
