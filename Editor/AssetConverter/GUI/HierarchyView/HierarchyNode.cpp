#include "HierarchyNode.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(HierarchyNode, const SharedRef<GameObject>& obj)
{
  this->visible_ = true;
  this->double_click_frame_ = -1;
  this->name_ = obj->GetName();
  this->object_ = obj;
  const T_UINT32 children_count = this->object_->GetChildrenCount();
  for (T_UINT32 i = 0; i < children_count; ++i)
  {
    this->children_.emplace_back(HierarchyNode::Create(obj->GetChild(i)));
  }
  return true;
}

// =================================================================
// Methdos
// =================================================================
void HierarchyNode::EditHierarchyWithImGUI(T_UINT32 level, T_UINT32* id, SharedRef<HierarchyNode>* selected)
{
  if (this->double_click_frame_ != -1)
  {
    ++this->double_click_frame_;
  }

  ImGui::PushID(*id);

  //Tree Begin
  std::string display_name = this->name_;
  if (this->expanded_ || this->children_.size() == 0)
  {
    display_name = " " + display_name;
  }
  else
  {
    display_name = u8"-" + display_name;
  }
  for (T_UINT32 i = 0; i < level; ++i)
  {
    display_name = "  " + display_name;
  }

  if (this->renamed_)
  {
    char buf[255];
    memcpy(buf, this->name_.c_str(), this->name_.length() + 1);
    ImGui::InputText("", buf, 255);
    this->name_ = buf;

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    bool focused = GImGui->ActiveId == window->GetID("");
    if (!this->selected_ || (this->rename_focused_ && !focused))
    {
      this->renamed_ = false;
    }
    this->rename_focused_ = focused;
  }
  else
  {
    bool toggled = ImGui::Selectable(display_name.c_str(), this->selected_, ImGuiSelectableFlags_AllowDoubleClick);
    if (toggled)
    {
      static const T_UINT32 DOUBLE_CLICK_FRAME = 30;
      if (this->double_click_frame_ == -1)
      {
        this->double_click_frame_ = 0;
      }
      else if (this->double_click_frame_ < DOUBLE_CLICK_FRAME)
      {
        this->expanded_ = !this->expanded_;
        this->double_click_frame_ = -1;
      }
      else
      {
        this->renamed_ = true;
        this->rename_focused_ = false;
        this->double_click_frame_ = -1;
      }
      this->selected_ = true;
    }
  }

  if (this->selected_)
  {
    if ((*selected) && (*selected) != this)
    {
      (*selected)->selected_ = false;
      (*selected)->double_click_frame_ = -1;
    }
    (*selected) = SharedRef<HierarchyNode>(this);
  }

  bool child_selected = false;
  //Tree Contents
  if (this->expanded_)
  {
    for (const SharedRef<HierarchyNode>& child : this->children_)
    {
      ++(*id);
      child->EditHierarchyWithImGUI(level + 1, id, selected);
      if (this->selected_)
      {
        child->selected_ = false;
      }
    }
  }

  ImGui::PopID();
}

bool HierarchyNode::EditWithImGUI(T_UINT32 id)
{
  return false;
}
