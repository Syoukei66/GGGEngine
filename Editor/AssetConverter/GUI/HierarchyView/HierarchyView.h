#pragma once

#include "HierarchyNode.h"

class HierarchyView
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(HierarchyView);

  // =================================================================
  // Methods
  // =================================================================
public:
  static void StartViewer(Scene* scene);
  static void EndViewer();

  static void EditWithImGUI();

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<HierarchyNode> root2d_;
  SharedRef<HierarchyNode> root3d_;

  SharedRef<HierarchyNode> selected_;

};
