#include "GameObjectRenderState.h"
#include "GameObject.h"

#include "Director.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObjectRenderState::GameObjectRenderState(Camera* camera)
  : camera_(camera)
  , layer_state_(1)
{
  this->matrix_stack_ = INativeMatrixStack::Create();
  this->view_proj_matrix_ = INativeMatrix::Create();
  this->world_view_proj_matrix_ = INativeMatrix::Create();
}

GameObjectRenderState::~GameObjectRenderState()
{
  delete this->matrix_stack_;
  delete this->view_proj_matrix_;
  delete this->world_view_proj_matrix_;
}

// =================================================================
// Method
// =================================================================
void GameObjectRenderState::Init()
{
  this->render_object_ = Director::GetInstance()->GetDevice();
  this->view_proj_matrix_->Assign(*this->camera_->GetViewMatrix());
  this->view_proj_matrix_->Multiple(*this->camera_->GetProjectionMatrix());
}

void GameObjectRenderState::PushMatrix(INativeMatrix* matrix)
{
  this->matrix_stack_->Push(matrix->GetNativeInstance());
}

void GameObjectRenderState::PopMatrix()
{
  this->matrix_stack_->Pop();
}

// =================================================================
// Setter / Getter
// =================================================================
INativeMatrix* GameObjectRenderState::GetWorldViewProjToMaterial()
{
  this->world_view_proj_matrix_->Assign(this->matrix_stack_->GetTop());
  this->world_view_proj_matrix_->Multiple(*this->view_proj_matrix_);
  return this->world_view_proj_matrix_;
}

