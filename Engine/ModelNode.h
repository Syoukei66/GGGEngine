#pragma once

#include <string>
#include <map>
#include <fbxsdk.h>
#include "GameObject3D.h"
#include "FbxNodeData.h"

class ModelNode : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelNode(const FbxNodeData& node);

  // =================================================================
  // Method for/from Interface/SuperClass
  // =================================================================
public:
  void NativeDraw(GameObject3DRenderState* state) override;

  // =================================================================
  // Method
  // =================================================================
public:
  ModelNode* FindFromChildren(const char* name);
  ModelNode* FindFromTree(const char* name);

  // =================================================================
  // Data Member
  // =================================================================
private:
  const FbxNodeData& node_;
  const T_UINT8 child_count_;
  ModelNode** children_;

  ModelNode* parent_;
};