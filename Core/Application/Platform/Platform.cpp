#include "Platform.h"

#include <imgui/imgui.h>

// =================================================================
// Methods
// =================================================================
bool Platform::Init(const ApplicationOption& option)
{
  this->graphics_api_ = this->CreateGraphicsAPI(option);
  this->audio_api_ = this->CreateAudioAPI(option);
  this->input_api_ = this->CreateInputAPI(option);
  return true;
}

bool Platform::Uninit()
{
  this->input_api_ = nullptr;
  this->audio_api_ = nullptr;
  this->graphics_api_ = nullptr;
  return true;
}
