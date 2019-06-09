#include "AssetEntityFileNode.h"
#include <Entity/AssetMetaData.h>
#include <regex>

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL(AssetEntityFileNode)
{
  return true;
}

// =================================================================
// Methdos
// =================================================================
void AssetEntityFileNode::AddAssetEntity(const SharedRef<AssetEntity>& entity)
{
  this->AddAssetEntity(entity->GetMetaData()->GetURI().GetFullPath(), entity);
}

SharedRef<AssetEntity> AssetEntityFileNode::SelectWithImGUI()
{
  SharedRef<AssetEntity> selected = nullptr;
  for (const auto& pair : this->children_)
  {
    if (ImGui::TreeNode(pair.first.c_str()))
    {
      if (!selected)
      {
        selected = pair.second->SelectWithImGUI();
      }
      ImGui::TreePop();
    }
  }
  for (const auto& pair : this->leafs_)
  {
    ImGui::Bullet();
    if (ImGui::Selectable(pair.first.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick))
    {
      if (!selected)
      {
        selected = pair.second->GetEntity();
      }
    }
  }
  return selected;
}

void AssetEntityFileNode::AddAssetEntity(std::string rest_path, const SharedRef<AssetEntity>& entity)
{
  std::regex re("(.+?)[/\\\\](.+)");
  std::smatch result;
  if (!std::regex_match(rest_path, result, re))
  {
    this->AddLeaf(rest_path, entity);
    return;
  }
  std::string node_name = result[1];
  SharedRef<AssetEntityFileNode> node = this->AddNode(result[1]);
  node->AddAssetEntity(result[2], entity);
}

SharedRef<AssetEntityFileNode> AssetEntityFileNode::AddNode(std::string node_name)
{
  const auto& itr = this->children_.find(node_name);
  if (itr == this->children_.end())
  {
    this->children_[node_name] = AssetEntityFileNode::Create();
  }
  return this->children_[node_name];
}

void AssetEntityFileNode::AddLeaf(std::string leaf_name, const SharedRef<AssetEntity>& entity)
{
  SharedRef<AssetEntityFileLeaf> leaf = AssetEntityFileLeaf::Create(entity);
  this->leafs_[leaf_name] = leaf;
}
