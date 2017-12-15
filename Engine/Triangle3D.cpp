#include "Triangle3D.h"
#include "VertexBufferObject_Primitive3D_Triangle.h"

Triangle3D::Triangle3D()
  : Shape3D(new VertexBufferObject_Primitive3D_Triangle())
{
}
