#include "ImGuiUtil.h"

void ImGui::Begin(const ActivityContext& context, const char* name, T_FLOAT padding, T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h)
{
  const T_FLOAT screen_width = context.GetOption().window_size.width - padding * 2;
  const T_FLOAT screen_height = context.GetOption().window_size.height - padding * 2;
  ImGui::SetNextWindowPos(ImVec2(padding + x * screen_width, padding + y * screen_height), ImGuiCond_Once);
  ImGui::SetNextWindowSize(ImVec2(w * screen_width, h * screen_height), ImGuiCond_Once);
  ImGui::Begin(name);
}
