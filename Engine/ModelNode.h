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
  virtual ~ModelNode();

  // =================================================================
  // Method
  // =================================================================
public:
  ModelNode* FindFromChildren(const char* name);
  ModelNode* FindFromTree(const char* name);

  void SetShader(const ShaderResource& shader);
  void SetShaderForChildren(const ShaderResource& shader);
  void SetShaderForChildren(const char* name, const ShaderResource& shader);
  void SetShaderForTree(const ShaderResource& shader);
  void SetShaderForTree(const char* name, const ShaderResource& shader);

  // =================================================================
  // Data Member
  // =================================================================
private:
  const FbxNodeData& node_;
  const T_UINT8 child_count_;
  ModelNode** children_;

  ModelNode* parent_;
};