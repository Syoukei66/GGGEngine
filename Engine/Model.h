#pragma once

#include "GameObject3D.h"

class Model : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  //TODO:���ModelData�ƕ�����
  Model(const char* path);
  ~Model();

  // =================================================================
  // Method
  // =================================================================
public:
  void NativeDraw(GameObject3DRenderState* state) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  LP_MODEL model_;
};