#pragma once

#include "Primitive3D.h"
#include "Texture.h"

class Shape3D : public Primitive3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Shape3D(IVertexBufferObject* vbo);
  virtual ~Shape3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  void NativeDraw(GameObject3DRenderState* state) override;

};