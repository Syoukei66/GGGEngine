#include "ModelNode.h"
#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelNode::ModelNode(const FbxNodeData& node)
  : node_(node)
  , child_count_(node.GetChildCount())
  , parent_(nullptr)
{
  this->SetMaterial(EngineAsset::Material::MODEL);
  this->children_ = new ModelNode*[this->child_count_];
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i] = new ModelNode(*node.GetChild(i));
    this->children_[i]->parent_ = this;
    this->AddChild(this->children_[i]);
  }
}

// =================================================================
// Method for/from Interface/SuperClass
// =================================================================
void ModelNode::NativeDraw(GameObject3DRenderState* state)
{
  const Mesh* mesh = this->node_.GetMesh();
  if (!mesh)
  {
    return;
  }
  mesh->Draw();
}

// =================================================================
// Method
// =================================================================
ModelNode* ModelNode::FindFromChildren(const char* name)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    if (this->children_[i]->node_.GetName() == name)
    {
      return this->children_[i];
    }
  }
  return nullptr;
}

ModelNode* ModelNode::FindFromTree(const char* name)
{
  ModelNode* ret = this->FindFromChildren(name);
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

// =================================================================
// Method
// =================================================================
