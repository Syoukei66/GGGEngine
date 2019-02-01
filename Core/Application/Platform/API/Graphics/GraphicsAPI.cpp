#include "GraphicsAPI.h"
#include <Core/Application/Activity/Activity.h>
#include <imgui/imgui.h>

// =================================================================
// Methods
// =================================================================
bool GraphicsAPI::Draw(const SharedRef<Activity>& activity, const std::function<void()>& draw_method)
{
  if (this->PreDraw())
  {
    const TVec2f& screen_size = activity->GetContext()->GetOption().window_size;
    this->SetViewport(0.0f, 0.0f, screen_size.width, screen_size.height, 0.0f, 1.0f);
    this->ViewportClear(TColor::BLACK);
    draw_method();
    ImGui::Render();
    this->PostDraw();
  }
  return true;
}
