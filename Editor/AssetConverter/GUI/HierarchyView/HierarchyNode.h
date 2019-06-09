#pragma once

class HierarchyNode : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(HierarchyNode);
  GG_CREATE_FUNC_1(HierarchyNode, const SharedRef<GameObject>&, obj);

  // =================================================================
  // Methdos
  // =================================================================
public:
  void EditHierarchyWithImGUI(T_UINT32 level, T_UINT32* id, SharedRef<HierarchyNode>* selected);
  bool EditWithImGUI(T_UINT32 id);

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<GameObject> object_;
  std::vector<SharedRef<HierarchyNode>> children_;

  std::string name_;
  bool visible_;
  bool renamed_;
  bool rename_focused_;
  bool expanded_;
  bool selected_;
  T_INT32 double_click_frame_;
};
