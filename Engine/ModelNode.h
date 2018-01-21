#pragma once

#include <string>
#include <map>
#include <fbxsdk.h>
#include "GameObject3D.h"

class ModelNode : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ModelNode(const FbxNode& node);

  // =================================================================
  // Method
  // =================================================================
public:
  ModelNode* FindFromChildren(const std::string& name);
  ModelNode* FindFromTree(const std::string& name);
  void AddChild(ModelNode* node);
  void RemoveChild(ModelNode* node);
  void RemoveSelf() override;
  void ClearChildren() override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  const FbxNode& node_;

  ModelNode* parent_;
  std::map<std::string, ModelNode*> children_;

};