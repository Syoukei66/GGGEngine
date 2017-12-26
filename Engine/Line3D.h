#pragma once

#include "Primitive3D.h"

class Line3D : public Primitive3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Line3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  void NativeDraw(GameObject3DRenderState* state) override;

};