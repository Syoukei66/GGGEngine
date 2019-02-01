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

void HierarchyView::EditWithImGUI()
{
  HierarchyView* self = &Self();

  ImGui::SetNextWindowPos(ImVec2(Application::GetMainActivity()->GetContext()->GetScreenWidth() - 250.0f - 20.0f, 20.0f), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(250.0f, 600.0f), ImGuiSetCond_Once);

  ImGui::Begin("Hierarchy");

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
