#pragma once

#include <fbxsdk.h>
#include "FbxNodeData.h"

class FbxData
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static FbxData* Create(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  FbxData(FbxScene* scene);

public:
  ~FbxData();

  // =================================================================
  // Methods
  // =================================================================
public:
  
  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  FbxNode& GetRootNode() const
  {
    return *this->scene_->GetRootNode();
  }

  FbxNodeData& GetRootData() const
  {
    return *this->root_data_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  FbxScene* scene_;
  FbxNodeData* root_data_;
};
