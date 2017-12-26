#pragma once

#include "Shape3D.h"

class BillBoard : public Shape3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  BillBoard();
  ~BillBoard();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  void PushMatrixStack(GameObject3DRenderState* state) override;
  void PopMatrixStack(GameObject3DRenderState* state) override;
  
  // =================================================================
  // Data Member
  // =================================================================
private:
  INativeMatrix* mat_;

};
