#pragma once

#include "ModelNode.h"
#include "FbxData.h"

class Model : public ModelNode
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Model(const FbxData& data);
  ~Model();

  // =================================================================
  // Method
  // =================================================================
public:
  void ManagedDraw(GameObject3DRenderState* state) override;
  void NativeDraw(GameObject3DRenderState* state) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  const FbxData& data_;

};