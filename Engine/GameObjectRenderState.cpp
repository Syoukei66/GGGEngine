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
}

void GameObjectRenderState::PushMatrix(INativeMatrix* matrix)
{
  this->matrix_stack_->Push(matrix->GetNativeInstance());
  //NativeMethod::Graphics().Graphics_SetTransformWorld(this->matrix_stack_->GetTop());
}

void GameObjectRenderState::PopMatrix()
{
  this->matrix_stack_->Pop();
}
