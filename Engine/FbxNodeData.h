#pragma once

#include "fbxsdk.h"
#include "Mesh.h"
#include "FbxMeshMaterial.h"

class FbxNodeData
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FbxNodeData(FbxNode* node);
  ~FbxNodeData();

  // =================================================================
  // Method
  // =================================================================
public:
  FbxNodeData* FindFromChildren(const char* name);
  FbxNodeData* FindFromTree(const char* name);

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline const T_UINT8 GetChildCount() const
  {
    return this->child_count_;
  }

  inline const FbxNodeData* GetChild(T_UINT8 index) const
  {
    return this->children_[index];
  }

  inline const char* GetName() const
  {
    return this->node_->GetName();
  }

  inline const Mesh* GetMesh() const
  {
    return this->mesh_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  FbxNode* node_;
  const T_UINT8 child_count_;
  FbxNodeData** children_;
  FbxMeshMaterial* mesh_material_;
  Mesh* mesh_;

  FbxNodeData* parent_;
};