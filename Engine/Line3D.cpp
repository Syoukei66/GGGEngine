#include "Line3D.h"
#include "VertexBufferObject_Primitive3D_Line.h"
#include "GameObject3DRenderState.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Line3D::Line3D()
  : Primitive3D(new VertexBufferObject_Primitive3D_Line())
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Line3D::NativeDraw(GameObject3DRenderState* state)
{
  Vertex* vertexes = (Vertex*)this->vbo_->GetVertexes();
  T_UINT32 size = this->vbo_->GetVertexesCount();
  NativeMethod::Graphics().Graphics_DrawIndexedVertexes(
    state,
    this->vbo_->GetPrimitiveType(),
    this->vbo_->GetVertexType(),
    vertexes,
    size,
    this->vbo_->GetIndexes()
  );
}
