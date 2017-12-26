#pragma once

#include "Shape3D.h"

class MeshField : public Shape3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MeshField(T_FLOAT width, T_FLOAT height, T_UINT16 x_num, T_UINT16 y_num);

};