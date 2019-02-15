#pragma once

#include <Engine/Scene/Scene.h>
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

  static void EditWithImGUI(const ActivityContext& activity_context);

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<HierarchyNode> root_;
  SharedRef<HierarchyNode> selected_;

};
