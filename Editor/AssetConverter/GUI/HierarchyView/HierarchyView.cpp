#include "HierarchyView.h"
#include <Util/ImGuiUtil.h>

// =================================================================
// Methods
// =================================================================
void HierarchyView::StartViewer(Scene* scene)
{
  HierarchyView* self = &Self();
  self->root_ = HierarchyNode::Create(scene->GetRoot());
}

void HierarchyView::EndViewer()
{
  HierarchyView* self = &Self();
  self->root_ = nullptr;
  self->selected_ = nullptr;
}

void HierarchyView::EditWithImGUI(const ActivityContext& activity_context)
{
  HierarchyView* self = &Self();

  ImGui::Begin(activity_context, u8"Hierarchy", 10.0f, 0.75f, 0.0f, 0.25f, 1.0f);

  T_UINT32 id = 0;

  //self->root_->EditHierarchyWithImGUI(0, &id, &self->selected_);

  ImGui::End();
}
