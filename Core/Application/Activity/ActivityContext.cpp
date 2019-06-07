#include "ActivityContext.h"
#include <imgui/imgui.h>
#include <imgui/imgui_ja_gryph_ranges.h>
#include <imgui/imgui_internal.h>

// =================================================================
// Methods
// =================================================================
void ActivityContext::Start(const ActivityOption& ao, const InputSetting& input_setting)
{
  ImGuiContext* context = ImGui::GetCurrentContext();
  this->option_ = ao;

  this->input_context_ = new InputContext(input_setting);

  IMGUI_CHECKVERSION();
  this->imgui_context_.reset(ImGui::CreateContext());
  this->imgui_context_->IO.IniFilename = NULL;
  ImGui::SetCurrentContext(this->imgui_context_.get());
  ImGui::StyleColorsDark(&this->imgui_context_->Style);
  ImGui::SetupJapaneseString(this->imgui_context_.get());
  this->OnStart(ao);
  ImGui::SetCurrentContext(context);
}

void ActivityContext::End()
{
  ImGuiContext* context = ImGui::GetCurrentContext();
  ImGui::SetCurrentContext(this->imgui_context_.get());
  this->OnEnd();
  ImGui::DestroyContext(this->imgui_context_.release());
  this->imgui_context_ = nullptr;
  
  delete this->input_context_;
  this->input_context_ = nullptr;
  ImGui::SetCurrentContext(context);
}

void ActivityContext::NewFrame(const SharedRef<Activity>& activity, const SharedRef<Platform>& platform)
{
  ImGui::SetCurrentContext(this->imgui_context_.get());

  this->OnNewFrame();
  platform->ImGuiNewFrame();
  platform->GetGraphicsAPI()->ImGuiNewFrame();
  ImGui::NewFrame();

  const T_FLOAT delta_time = Application::GetUpdateEventState().GetDeltaTime();

  this->elapsed_time_ += delta_time;

  this->input_context_->Update(activity, platform->GetInputAPI());
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

void ActivityContext::Show()
{
  if (this->IsVisible())
  {
    return;
  }
  this->OnShow();
}

void ActivityContext::Hide()
{
  if (!this->IsVisible())
  {
    return;
  }
  this->OnHide();
}
