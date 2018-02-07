#pragma once

#include "GameObject3D.h"
#include "Mesh.h"

class Plane3D : public GameObject3D
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static Plane3D* Create();

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  Plane3D() {}
  
};
