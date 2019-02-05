#include "InputContext.h"

#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Input/InputState.h>
#include <Core/Application/Activity/Activity.h>

// =================================================================
// Constructor / Destructor
// =================================================================
InputContext::InputContext(const InputSetting& setting)
{
  this->enable_state_ = setting.enable_state_;
  this->state_count_ = setting.player_count_;
  this->states_ = new InputState*[this->state_count_]();
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    this->states_[i] = new InputState(i, setting);
  }
}

InputContext::~InputContext()
{
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    delete this->states_[i];
  }
  delete[] this->states_;
}

// =================================================================
// Methods
// =================================================================
void InputContext::Update(const SharedRef<Activity>& activity, const SharedRef<InputAPI>& api)
{
  if (this->enable_state_ == EnableState::ONLY_ON_FOCUS && !activity->GetContext().IsActive())
  {
    return;
  }
  this->engine_input_state_.Prepare();
  api->InputProcess(activity, &this->engine_input_state_);
  if (this->enable_state_ == EnableState::ONLY_ON_MOUSE && !this->IsOnCursol())
  {
    return;
  }
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    this->states_[i]->Update(this->engine_input_state_);
  }
}

bool InputContext::IsOnCursol()
{
  using namespace EngineInput::Analog;
  const T_FLOAT x = this->engine_input_state_.GetAnalogInput(0).GetValue(this->cursol_input_id_, DIMENSION_X, 0.0f);
  const T_FLOAT y = this->engine_input_state_.GetAnalogInput(0).GetValue(this->cursol_input_id_, DIMENSION_Y, 0.0f);
  return -1.0f < x && x < 1.0f && -1.0f < y && y < 1.0f;
}
