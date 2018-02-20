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
  this->SetRenderer(MeshRenderer::Create(*node.GetMesh(), this));
  T_UINT8 material_count = node.GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    this->GetRenderer()->AddMaterial(*node.GetMaterial(i));
  }
  this->children_ = new ModelNode*[this->child_count_];
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i] = new ModelNode(*node.GetChild(i));
    this->children_[i]->parent_ = this;
    this->AddChild(this->children_[i]);
  }
  this->GetTransform()->SetPosition(node.GetTranslate());
  this->GetTransform()->SetScale(node.GetScaling());
  this->GetTransform()->RotateX(node.GetRotation().x);
  this->GetTransform()->RotateY(node.GetRotation().y);
  this->GetTransform()->RotateZ(node.GetRotation().z);
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
  this->GetRenderer()->GetMaterial()->SetShader(shader);
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

void ModelNode::SetMaterial(Material& material)
{
  this->GetRenderer()->SetMaterial(material);
}

void ModelNode::SetMaterialForChildren(Material& material)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetMaterial(material);
  }
}

void ModelNode::SetMaterialForChildren(const char* name, Material& material)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    if (strcmp(this->children_[i]->node_.GetName(), name) == 0)
    {
      this->children_[i]->SetMaterial(material);
    }
  }
}

void ModelNode::SetMaterialForTree(Material& material)
{
  this->SetMaterial(material);
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetMaterialForTree(material);
  }
}

void ModelNode::SetMaterialForTree(const char* name, Material& material)
{
  if (strcmp(this->node_.GetName(), name) == 0)
  {
    this->SetMaterial(material);
  }
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetMaterialForTree(name, material);
  }
}

void ModelNode::SetLayerIdForChildren(T_UINT8 id)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetLayerId(id);
  }
}

void ModelNode::SetLayerIdForChildren(const char* name, T_UINT8 id)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    if (strcmp(this->children_[i]->node_.GetName(), name) == 0)
    {
      this->children_[i]->SetLayerId(id);
    }
  }
}

void ModelNode::SetLayerIdForTree(T_UINT8 id)
{
  this->SetLayerId(id);
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetLayerIdForTree(id);
  }
}

void ModelNode::SetLayerIdForTree(const char* name, T_UINT8 id)
{
  if (strcmp(this->node_.GetName(), name) == 0)
  {
    this->SetLayerId(id);
  }
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i]->SetLayerIdForTree(name, id);
  }
}
