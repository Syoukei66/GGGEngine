#pragma once
//
//#include <string>
//#include <map>
//#include "GameObject3D.h"
//#include "ModelData.h"
//
//class Model;
//
//class ModelNode : public GameObject3D
//{
//  // =================================================================
//  // Constructor / Destructor
//  // =================================================================
//public:
//  ModelNode(const ModelNodeData* node);
//  virtual ~ModelNode();
//
//  // =================================================================
//  // Method
//  // =================================================================
//public:
//  ModelNode* FindFromChildren(const char* name);
//  ModelNode* FindFromTree(const char* name);
//
//  void SetShader(const ShaderAsset& shader);
//  void SetShaderForChildren(const ShaderAsset& shader);
//  void SetShaderForChildren(const char* name, const ShaderAsset& shader);
//  void SetShaderForTree(const ShaderAsset& shader);
//  void SetShaderForTree(const char* name, const ShaderAsset& shader);
//
//  void SetMaterial(rcMaterial& material);
//  void SetMaterialForChildren(rcMaterial& material);
//  void SetMaterialForChildren(const char* name, rcMaterial& material);
//  void SetMaterialForTree(rcMaterial& material);
//  void SetMaterialForTree(const char* name, rcMaterial& material);
//
//  void SetLayerIdForChildren(T_UINT8 id);
//  void SetLayerIdForChildren(const char* name, T_UINT8 id);
//  void SetLayerIdForTree(T_UINT8 id);
//  void SetLayerIdForTree(const char* name, T_UINT8 id);
//
//  // =================================================================
//  // Data Member
//  // =================================================================
//private:
//  const ModelNodeData* const node_;
//  const T_UINT8 child_count_;
//  ModelNode** children_;
//
//  ModelNode* parent_;
//};