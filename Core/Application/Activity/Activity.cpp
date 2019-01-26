#include "Activity.h"

#include <chrono>

#include <Core/Application/Object/ObjectManager.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>

#include <Core/Application/Platform/Platform.h>
#include <imgui/imgui.h>
#include <imgui/imgui_ja_gryph_ranges.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(Activity, const ActivityOption& option)
{
  this->option_ = option;
  return true;
}

// =================================================================
// Methods
// =================================================================
void Activity::Start()
{
  IMGUI_CHECKVERSION();
  this->imgui_context_ = ImGui::CreateContext();
  ImGui::SetCurrentContext(this->imgui_context_);

  this->OnStart();

  ImGui::StyleColorsDark();
  ImGui::SetupJapaneseString();

  this->scene_manager_ = new SceneManager();
}

void Activity::End()
{
  this->scene_manager_->ClearScene();
  delete this->scene_manager_;

  ImGui::DestroyContext(this->imgui_context_);
  this->imgui_context_ = nullptr;

  this->OnEnd();
}

bool Activity::Update(const SharedRef<GraphicsAPI>& graphics_api, const SharedRef<InputAPI>& input_api)
{
  ImGui::SetCurrentContext(this->imgui_context_);
  ImGui::NewFrame();

  this->update_event_state_.Update();
  input_api->Update();
  this->scene_manager_->Update(this->update_event_state_);
  
  // •`‰æŽüŠú‚ª—ˆ‚½‚ç•`‰æ‚ðs‚¤
  if (this->DrawEnabled(this->update_event_state_.GetDeltaTime()))
  {
    ImGui::Render();
    graphics_api->Draw(SharedRef<Activity>(this), [&]()
    {
      this->scene_manager_->Draw();
    });
  }

  ImGui::EndFrame();
  return true;
}

bool Activity::DrawEnabled(T_FLOAT delta_time)
{
  this->elapsed_time_ += delta_time;
  if (this->elapsed_time_ >= this->option_.render_cycle)
  {
    this->elapsed_time_ = fmodf(this->elapsed_time_, this->option_.render_cycle);
    return true;
  }
  return false;
}
