#include "DirectInputDevice_XInput.h"

DirectInputDevice_XInput::DirectInputDevice_XInput(T_UINT8 handler, T_UINT8 user_index, const XInputInput* inputs, T_UINT8 inputs_count, EngineInput::Analog::ID left, EngineInput::Analog::ID right, EngineInput::Analog::ID trigger)
  : DirectInputDevice(handler)
  , user_index_(user_index)
  , inputs_(inputs)
  , inputs_count_(inputs_count)
  , left_(left)
  , right_(right)
  , trigger_(trigger)
{}

bool DirectInputDevice_XInput::Init(const SharedRef<Activity>& activity, LPDIRECTINPUT8 input)
{
  return true;
}

bool DirectInputDevice_XInput::Uninit(LPDIRECTINPUT8 input)
{
  return true;
}

void DirectInputDevice_XInput::InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state)
{
  DWORD dw_result;
  ZeroMemory(&this->xstate_, sizeof(XINPUT_STATE));
  T_INT8 success_count = -1;
  for (T_UINT8 i = 0; i < 4; ++i)
  {
    dw_result = XInputGetState(i, &this->xstate_);
    if (dw_result == ERROR_SUCCESS)
    {
      ++success_count;
      if (success_count >= this->user_index_)
      {
        break;
      }
    }
  }
  if (dw_result != ERROR_SUCCESS)
  {
    return;
  }
}

void DirectInputDevice_XInput::ApplyProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state)
{  
  // Zero value if thumbsticks are within the dead zone 
  if ((this->xstate_.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
    this->xstate_.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
    (this->xstate_.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
      this->xstate_.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
  {
    this->xstate_.Gamepad.sThumbLX = 0;
    this->xstate_.Gamepad.sThumbLY = 0;
  }

  if ((this->xstate_.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
    this->xstate_.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
    (this->xstate_.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
      this->xstate_.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
  {
    this->xstate_.Gamepad.sThumbRX = 0;
    this->xstate_.Gamepad.sThumbRY = 0;
  }

  //trigger
  state->PreInputAnalog(handler, this->trigger_);
  const T_FLOAT trigger_x = this->xstate_.Gamepad.bLeftTrigger / 255.0f;
  const T_FLOAT trigger_y = this->xstate_.Gamepad.bRightTrigger / 255.0f;
  state->InputAnalog(handler, this->trigger_, 0, trigger_x);
  state->InputAnalog(handler, this->trigger_, 1, trigger_y);
  state->PostInputAnalog(handler, this->trigger_);

  //thumbL
  state->PreInputAnalog(handler, this->left_);
  const T_FLOAT thumbL_x = this->xstate_.Gamepad.sThumbLX / 32767.0f;
  const T_FLOAT thumbL_y = this->xstate_.Gamepad.sThumbLY / 32767.0f;
  state->InputAnalog(handler, this->left_, 0, thumbL_x);
  state->InputAnalog(handler, this->left_, 1, thumbL_y);
  state->PostInputAnalog(handler, this->left_);

  //thumbR
  state->PreInputAnalog(handler, this->right_);
  const T_FLOAT thumbR_x = this->xstate_.Gamepad.sThumbRX / 32767.0f;
  const T_FLOAT thumbR_y = this->xstate_.Gamepad.sThumbRY / 32767.0f;
  state->InputAnalog(handler, this->right_, 0, thumbR_x);
  state->InputAnalog(handler, this->right_, 1, thumbR_y);
  state->PostInputAnalog(handler, this->right_);

  //button
  for (T_UINT8 i = 0; i < this->inputs_count_; ++i)
  {
    state->PreInputDigital(handler, this->inputs_[i].id);
    if (this->xstate_.Gamepad.wButtons & this->inputs_[i].input)
    {
      state->InputDigital(handler, this->inputs_[i].id);
    }
    state->PostInputDigital(handler, this->inputs_[i].id);
  }

}
