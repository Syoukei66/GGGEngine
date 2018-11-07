#include "InputAPI.h"
#include <Core/Application/Activity/ActivityOption.h>

// =================================================================
// Methods
// =================================================================
GG_INIT_FUNC_IMPL_1(InputAPI, const InputSetting& setting)
{
  this->state_count_ = setting.player_count_;
  this->states_ = new InputState*[this->state_count_]();
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    this->states_[i] = new InputState(i, setting);
  }
  return true;
}

GG_DESTRUCT_FUNC_IMPL(InputAPI)
{
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    delete this->states_[i];
  }
  delete[] this->states_;
  return true;
}

void InputAPI::Update()
{
  this->InputProcess(&this->engine_input_state_);
  for (T_UINT8 i = 0; i < this->state_count_; ++i)
  {
    this->states_[i]->Update(this->engine_input_state_);
  }
}
