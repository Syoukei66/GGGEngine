#include "Cube3D.h"
#include "VertexBufferObject_Primitive3D_Cube.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Cube3D::Cube3D()
  : Shape3D(new VertexBufferObject_Primitive3D_Cube())
{
}
