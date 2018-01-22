#include "FbxNodeData.h"

// =================================================================
// Constructor / Destructor
// =================================================================
FbxNodeData::FbxNodeData(FbxNode* node)
  : node_(node)
  , child_count_(node->GetChildCount())
  , mesh_material_(nullptr)
  , mesh_(nullptr)
{
  FbxMesh* mesh = node->GetMesh();
  if (mesh)
  {
    this->mesh_material_ = new FbxMeshMaterial(mesh);
    this->mesh_ = new Mesh(*this->mesh_material_);
  }
  this->children_ = new FbxNodeData*[this->child_count_];
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i] = new FbxNodeData(node->GetChild(i));
    this->children_[i]->parent_ = this;
  }
}

FbxNodeData::~FbxNodeData()
{
  delete this->mesh_;
  delete this->mesh_material_;
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    delete this->children_[i];
  }
  delete[] this->children_;
}

// =================================================================
// Method
// =================================================================
FbxNodeData* FbxNodeData::FindFromChildren(const char* name)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    if (strcmp(name, this->children_[i]->node_->GetName()) == 0)
    {
      return this->children_[i];
    }
  }
  return nullptr;
}

FbxNodeData* FbxNodeData::FindFromTree(const char* name)
{
  FbxNodeData* ret = this->FindFromChildren(name);
  if (ret)
  {
    return ret;
  }
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    ret = this->children_[i]->FindFromTree(name);
    if (ret)
    {
      return ret;
    }
  }
  return nullptr;
}
