#include "MeshField.h"
#include "VertexBufferObject_Primitive3D_MeshField.h"

MeshField::MeshField(T_FLOAT width, T_FLOAT height, T_UINT16 x_num, T_UINT16 y_num)
  : Shape3D(new VertexBufferObject_Primitive3D_MeshField(width, height, x_num, y_num))
{
}
