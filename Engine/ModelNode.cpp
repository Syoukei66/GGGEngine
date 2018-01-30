#include "ModelNode.h"
#include "EngineAsset.h"
#include "MeshRenderer.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ModelNode::ModelNode(const FbxNodeData& node)
  : node_(node)
  , child_count_(node.GetChildCount())
  , parent_(nullptr)
{
  this->SetRenderer(MeshRenderer::Create(*node.GetMesh()));
  this->GetRenderer()->SetMaterial(*node.GetMaterial());
  this->children_ = new ModelNode*[this->child_count_];
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i] = new ModelNode(*node.GetChild(i));
    this->children_[i]->parent_ = this;
    this->AddChild(this->children_[i]);
  }
}

ModelNode::~ModelNode()
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    delete this->children_[i];
  }
  delete[] this->children_;
}

// =================================================================
// Method
// =================================================================
ModelNode* ModelNode::FindFromChildren(const char* name)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    if (strcmp(this->children_[i]->node_.GetName(), name) == 0)
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

void ModelNode::SetShader(const ShaderResource& shader)
{  
  this->GetRenderer()->GetMaterial().SetShader(shader);
}

void ModelNode::SetShaderForChildren(const ShaderResource& shader)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetShader(shader);
  }
}

void ModelNode::SetShaderForChildren(const char* name, const ShaderResource& shader)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    if (strcmp(this->children_[i]->node_.GetName(), name) == 0)
    {
      this->children_[i]->SetShader(shader);
    }
  }
}

void ModelNode::SetShaderForTree(const ShaderResource& shader)
{
  this->SetShader(shader);
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetShaderForTree(shader);
  }
}

void ModelNode::SetShaderForTree(const char* name, const ShaderResource& shader)
{
  if (strcmp(this->node_.GetName(), name) == 0)
  {
    this->SetShader(shader);
  }
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetShaderForTree(name, shader);
  }
}
