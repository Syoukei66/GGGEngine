#include "GameObjectRenderState.h"
#include "GameObject.h"

#include "Director.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObjectRenderState::GameObjectRenderState()
  : layer_state_(1)
{
  this->matrix_stack_ = INativeMatrixStack::Create();
}

GameObjectRenderState::~GameObjectRenderState()
{
  delete this->matrix_stack_;
}

// =================================================================
// Method
// =================================================================
void GameObjectRenderState::Init()
{
  this->render_object_ = Director::GetInstance()->GetDevice();
  this->SetBlendMode(BlendFunction::BL_NOBLEND, BlendFunction::BL_NOBLEND, true);
}

void GameObjectRenderState::PushMatrix(INativeMatrix* matrix)
{
  this->matrix_stack_->Push(matrix->GetNativeInstance());
  NativeMethod::Graphics().Graphics_SetTransformWorld(this->matrix_stack_->GetTop());
}

void GameObjectRenderState::PopMatrix()
{
  this->matrix_stack_->Pop();
}

// =================================================================
// Setter / Getter
// =================================================================
void GameObjectRenderState::SetBlendMode(BlendFunction::BlendMode src, BlendFunction::BlendMode dst, bool force_update)
{
  if (!force_update && this->src_ == src && this->dst_ == dst)
  {
    return;
  }
  this->src_ = src;
  this->dst_ = dst;
  NativeMethod::Graphics().Graphics_SetBlendMode(this->src_, this->dst_);
}
