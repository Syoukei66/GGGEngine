#pragma once

#include <GUI/FileView/AssetEntityFileNode.h>
#include <Entity/AssetEntity.h>

class FileView
{
  // =================================================================
  // GGG Editor
  // =================================================================
  GG_SINGLETON(FileView);

  // =================================================================
  // Methdos
  // =================================================================
public:
  static void Init(AssetConverterContext* context);
  static void Uninit();

  static SharedRef<AssetEntity> SelectWithImGUI();

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<AssetEntityFileNode> root_;

};