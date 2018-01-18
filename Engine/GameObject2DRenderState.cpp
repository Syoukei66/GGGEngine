#include "GameObject2DRenderState.h"
#include "NativeMethod.h"
#include "Camera2D.h"

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

void GameObject2DRenderState::SetupViewProjMatrix(INativeMatrix* view_proj_matrix)
{
  view_proj_matrix->Assign(*this->camera_->GetProjectionMatrix());
  view_proj_matrix->MultipleReverse(*this->camera_->GetViewMatrix());
}
