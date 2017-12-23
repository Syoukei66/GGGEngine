#include "Camera3D_Transformed.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera3D_Transformed::Camera3D_Transformed(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera3D(x, y, width, height, z_min, z_max)
{
  this->entity_ = new GameObject3D();
}

Camera3D_Transformed::Camera3D_Transformed()
  : Camera3D()
{
  this->entity_ = new GameObject3D();
}

Camera3D_Transformed::~Camera3D_Transformed()
{
  delete this->entity_;
}
