#include "ModelNode.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelNode::ModelNode(const FbxNode& node)
  : node_(node)
  , parent_(nullptr)
  , children_()
{
}

ModelNode* ModelNode::FindFromChildren(const std::string& name)
{
  auto itr = this->children_.find(name);
  if (itr != this->children_.end())
  {
    return itr->second;
  }
  return nullptr;
}

ModelNode* ModelNode::FindFromTree(const std::string& name)
{
  ModelNode* ret = this->FindFromChildren(name);
  if (ret)
  {
    return ret;
  }
  for (auto pair : this->children_)
  {
    ret = pair.second->FindFromTree(name);
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
void ModelNode::AddChild(ModelNode* node)
{
  node->parent_ = this;
  this->children_[node->node_.GetName()] = node;
  GameObject3D::AddChild(node);
}

void ModelNode::RemoveChild(ModelNode* node)
{
  node->parent_ = nullptr;
  this->children_.erase(node->node_.GetName());
  GameObject3D::RemoveChild(node);
}

void ModelNode::RemoveSelf()
{
  GameObject3D::RemoveSelf();
  if (!this->parent_)
  {
    return;
  }
  this->parent_->RemoveChild(this);
}

void ModelNode::ClearChildren()
{
  for (auto pair : this->children_)
  {
    pair.second->parent_ = nullptr;
  }
  this->children_.clear();
  GameObject3D::ClearChildren();
}
