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

  inline Material* GetMaterial() const
  {
    return this->material_;
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

  Material* material_;

  //Color4F ambient_;
  //T_FLOAT ambient_factor_;

  //Color4F diffuse_;
  //T_FLOAT diffuse_factor_;

  //Color4F emissive_;
  //T_FLOAT emissive_factor_;

  //TVec3f bump_;
  //T_FLOAT bump_factor_;

  //Color4F specular_;
  //T_FLOAT specular_factor_;

  //T_FLOAT shininess_;

  //Color4F reflection_;
  //T_FLOAT reflection_factor_;

  //Color4F transparent_;
  //T_FLOAT transparent_factor_;

  Texture* normal_map_;
  Texture* bump_map_;
  Texture* texture_;

  FbxNodeData* parent_;
};