#include "GameObjectRenderState.h"
#include "GameObject.h"

#include "NativeMethod.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObjectRenderState::GameObjectRenderState()
  : layer_state_(0)
{
  this->matrix_stack_ = NativeMethod::Matrix().Matrix4x4Stack_Create();
}

GameObjectRenderState::~GameObjectRenderState()
{
  NativeMethod::Matrix().Matrix4x4Stack_Delete(this->matrix_stack_);
}

// =================================================================
// Method
// =================================================================
void GameObjectRenderState::Init()
{
  this->render_object_ = Director::GetInstance()->GetDevice();
  this->SetBlendMode(BlendFunction::BL_NOBLEND, BlendFunction::BL_NOBLEND, true);
}

void GameObjectRenderState::PushMatrix(LP_MATRIX_4x4 matrix)
{
  NativeMethod::Matrix().Matrix4x4Stack_Push(this->matrix_stack_, matrix);
  NativeMethod::Matrix().Matrix4x4Stack_Apply(this->render_object_, this->matrix_stack_);
}

void GameObjectRenderState::PopMatrix()
{
  NativeMethod::Matrix().Matrix4x4Stack_Pop(this->matrix_stack_);
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
