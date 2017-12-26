#include "BillBoard.h"
#include "VertexBufferObject_Primitive3D_Plane.h"
#include "Camera.h"
#include "GameObject3DRenderState.h"
#include "Camera3D.h"

BillBoard::BillBoard()
  : Shape3D(new VertexBufferObject_Primitive3D_Plane())
{
  this->mat_ = INativeMatrix::Create();
}

BillBoard::~BillBoard()
{
  delete this->mat_;
}

void BillBoard::PushMatrixStack(GameObject3DRenderState* state)
{
  state->PushMatrix(this->GetTransform()->GetMatrix());

  state->GetCamera()->GetViewMatrix()->Inverse(this->mat_);

  (*this->mat_)[3][0] = 0.0f;
  (*this->mat_)[3][1] = 0.0f;
  (*this->mat_)[3][2] = 0.0f;

  state->PushMatrix(this->mat_);
}

void BillBoard::PopMatrixStack(GameObject3DRenderState* state)
{
  state->PopMatrix();
  state->PopMatrix();
}
