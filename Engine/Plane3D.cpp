#include "Plane3D.h"
#include "VertexBufferObject_Primitive3D_Plane.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Plane3D::Plane3D()
  : Shape3D(new VertexBufferObject_Primitive3D_Plane())
{
}