#pragma once

#include "Vertex.h"
#include "GameObject3D.h"

class IVertexBufferObject;

class Primitive3D : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Primitive3D(IVertexBufferObject* vbo);
  virtual ~Primitive3D() {};

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;
  virtual void PreDraw(GameObject3DRenderState* state) override;

  // =================================================================
  // Data Member
  // =================================================================
protected:
  IVertexBufferObject* vbo_;

};
