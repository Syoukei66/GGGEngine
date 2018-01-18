#pragma once

#include "GameObject3D.h"
#include "ModelData.h"

class Model : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Model(const ModelData& data);
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
  const ModelData& data_;
};