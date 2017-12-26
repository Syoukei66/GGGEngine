#include "Primitive3D.h"
#include "NativeMethod.h"
#include "IVertexBufferObject.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Primitive3D::Primitive3D(IVertexBufferObject* vbo)
  : vbo_(vbo)
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Primitive3D::Init()
{
  GameObject3D::Init();
  this->vbo_->Init();
}

void Primitive3D::PreDraw(GameObject3DRenderState* state)
{
  this->vbo_->UpdateCoord(this);
  GameObject3D::PreDraw(state);
}
