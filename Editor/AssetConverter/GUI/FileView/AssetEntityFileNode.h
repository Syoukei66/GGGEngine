#pragma once

#include "AssetEntityFileLeaf.h"

class AssetEntityFileNode : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(AssetEntityFileNode);
  GG_CREATE_FUNC(AssetEntityFileNode) { return true; }

  // =================================================================
  // Methdos
  // =================================================================
public:
  void AddAssetEntity(AssetEntity* entity);
  AssetEntity* SelectWithImGUI();

protected:
  void AddAssetEntity(std::string rest_path, AssetEntity* entity);
  SharedRef<AssetEntityFileNode> AddNode(std::string node_name);
  void AddLeaf(std::string leaf_name, AssetEntity* entity);

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::map<std::string, SharedRef<AssetEntityFileNode>> children_;
  std::map<std::string, SharedRef<AssetEntityFileLeaf>> leafs_;

};