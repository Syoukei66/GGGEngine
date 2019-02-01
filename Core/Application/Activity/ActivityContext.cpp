#include "ActivityContext.h"
#include <imgui/imgui.h>
#include <imgui/imgui_ja_gryph_ranges.h>
#include <imgui/imgui_internal.h>

// =================================================================
// Methods
// =================================================================
void ActivityContext::Start(const ActivityOption& ao)
{
  this->option_ = ao;

  IMGUI_CHECKVERSION();
  this->imgui_context_.reset(ImGui::CreateContext());
  //ImGui::SetCurrentContext(this->imgui_context_);

  ImGui::StyleColorsDark();
  ImGui::SetupJapaneseString();
  //ImGui::StyleColorsDark(&this->imgui_context_->Style);
  //ImGui::SetupJapaneseString(this->imgui_context_);

  this->OnStart(ao);
}

void ActivityContext::End()
{
  this->OnEnd();

  ImGui::DestroyContext(this->imgui_context_.release());
  this->imgui_context_ = nullptr;
}

void ActivityContext::NewFrame(const SharedRef<Platform>& platform)
{
  //ImGui::SetCurrentContext(this->imgui_context_);

  platform->GetGraphicsAPI()->ImGuiNewFrame();
  ImGui::NewFrame();

  const T_FLOAT delta_time = Application::GetUpdateEventState().GetDeltaTime();

  this->elapsed_time_ += delta_time;

  platform->GetInputAPI()->Update();
}

void ActivityContext::EndFrame()
{
  if (this->DrawEnabled())
  {
    this->elapsed_time_ = fmodf(this->elapsed_time_, this->option_.render_cycle);
  }
  ImGui::EndFrame();
}

bool ActivityContext::DrawEnabled()
{
  return this->elapsed_time_ >= this->option_.render_cycle;
}
