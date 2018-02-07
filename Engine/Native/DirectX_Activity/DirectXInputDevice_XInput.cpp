#include "DirectXInputDevice_XInput.h"
#include <XInput.h>

DirectXInputDevice_XInput::DirectXInputDevice_XInput(T_UINT8 handler, T_UINT8 user_index, const XInputInput* inputs, T_UINT8 inputs_count, EngineInput::Analog::ID left, EngineInput::Analog::ID right, EngineInput::Analog::ID trigger)
  : DirectXInputDevice(handler)
  , user_index_(user_index)
  , inputs_(inputs)
  , inputs_count_(inputs_count)
  , left_(left)
  , right_(right)
  , trigger_(trigger)
{}

bool DirectXInputDevice_XInput::Init(LPDIRECTINPUT8 input)
{
  return true;
}

bool DirectXInputDevice_XInput::Uninit(LPDIRECTINPUT8 input)
{
  return true;
}

void DirectXInputDevice_XInput::InputProcess(T_UINT8 handler, EngineInputState* state)
{
  DWORD dw_result;
  XINPUT_STATE xstate;
  ZeroMemory(&xstate, sizeof(XINPUT_STATE));
  T_INT8 success_count = -1;
  for (T_UINT8 i = 0; i < 4; ++i)
  {
    dw_result = XInputGetState(i, &xstate);
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
  // Zero value if thumbsticks are within the dead zone 
  if ((xstate.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
    xstate.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
    (xstate.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
      xstate.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
  {
    xstate.Gamepad.sThumbLX = 0;
    xstate.Gamepad.sThumbLY = 0;
  }

  if ((xstate.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
    xstate.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
    (xstate.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
      xstate.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
  {
    xstate.Gamepad.sThumbRX = 0;
    xstate.Gamepad.sThumbRY = 0;
  }

  //trigger
  state->PreInputAnalog(handler, this->trigger_);
  const T_FLOAT trigger_x = xstate.Gamepad.bLeftTrigger / 255.0f;
  const T_FLOAT trigger_y = xstate.Gamepad.bRightTrigger / 255.0f;
  state->InputAnalog(handler, this->trigger_, 0, trigger_x);
  state->InputAnalog(handler, this->trigger_, 1, trigger_y);
  state->PostInputAnalog(handler, this->trigger_);

  //thumbL
  state->PreInputAnalog(handler, this->left_);
  const T_FLOAT thumbL_x = xstate.Gamepad.sThumbLX / 32767.0f;
  const T_FLOAT thumbL_y = xstate.Gamepad.sThumbLY / 32767.0f;
  state->InputAnalog(handler, this->left_, 0, thumbL_x);
  state->InputAnalog(handler, this->left_, 1, thumbL_y);
  state->PostInputAnalog(handler, this->left_);

  //thumbR
  state->PreInputAnalog(handler, this->right_);
  const T_FLOAT thumbR_x = xstate.Gamepad.sThumbRX / 32767.0f;
  const T_FLOAT thumbR_y = xstate.Gamepad.sThumbRY / 32767.0f;
  state->InputAnalog(handler, this->right_, 0, thumbR_x);
  state->InputAnalog(handler, this->right_, 1, thumbR_y);
  state->PostInputAnalog(handler, this->right_);

  //button
  for (T_UINT8 i = 0; i < this->inputs_count_; ++i)
  {
    state->PreInputDigital(handler, this->inputs_[i].id);
    if (xstate.Gamepad.wButtons & this->inputs_[i].input)
    {
      state->InputDigital(handler, this->inputs_[i].id);
    }
    state->PostInputDigital(handler, this->inputs_[i].id);
  }

}
