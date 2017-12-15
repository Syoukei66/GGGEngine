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
  LP_MATRIX_4x4 mat_;

};
