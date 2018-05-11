#pragma once

#include "fbxsdk.h"
#include "Mesh.h"
#include "FbxMeshMaterial.h"
#include "TextureResource.h"


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

  inline Material* GetMaterial(T_UINT8 index) const
  {
    return this->material_[index];
  }

  inline T_UINT8 GetMaterialCount() const
  {
    return this->material_count_;
  }

  inline const TVec3f& GetTranslate() const
  {
    return this->translate_;
  }

  inline const TVec3f& GetScaling() const
  {
    return this->scaling_;
  }

  inline const TVec3f& GetRotation() const
  {
    return this->rotation_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  FbxNode* node_;
  const T_UINT8 child_count_;
  FbxNodeData** children_;
  FbxMeshMaterial** mesh_materials_;
  T_UINT8 mesh_material_count_;
  Mesh* mesh_;

  Material** material_;
  T_UINT8 material_count_;

  TVec3f translate_;
  TVec3f scaling_;
  TVec3f rotation_;

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

  TextureResource* normal_map_;
  TextureResource* bump_map_;
  TextureResource* texture_;

  FbxNodeData* parent_;
};