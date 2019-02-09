#include "HierarchyView.h"

// =================================================================
// Methods
// =================================================================
void HierarchyView::StartViewer(Scene* scene)
{
  HierarchyView* self = &Self();
  self->root2d_ = HierarchyNode::Create(scene->GetRoot2d());
  self->root3d_ = HierarchyNode::Create(scene->GetRoot3d());
}

void HierarchyView::EndViewer()
{
  HierarchyView* self = &Self();
  self->root2d_ = nullptr;
  self->root3d_ = nullptr;
  self->selected_ = nullptr;
}

void HierarchyView::EditWithImGUI(const ActivityContext& activity_context)
{
  HierarchyView* self = &Self();

  ImGui::Begin(activity_context, u8"Hierarchy", 10.0f, 0.75f, 0.0f, 0.25f, 1.0f);

  T_UINT32 id = 0;

  if (ImGui::TreeNode(u8"2D"))
  {
    self->root2d_->EditHierarchyWithImGUI(0, &id, &self->selected_);
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(u8"3D"))
  {
    self->root3d_->EditHierarchyWithImGUI(0, &id, &self->selected_);
    ImGui::TreePop();
  }

  ImGui::End();
}
