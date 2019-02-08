#pragma once

#include "DirectInputDevice.h"
#include <XInput.h>

class DirectInputDevice_XInput : public DirectInputDevice
{
public:
  struct XInputInput
  {
    EngineInput::Digital::ID id;
    WORD input;
  };

public:
  DirectInputDevice_XInput(T_UINT8 handler, T_UINT8 user_index, const XInputInput* inputs, T_UINT8 inputs_count, EngineInput::Analog::ID left, EngineInput::Analog::ID right, EngineInput::Analog::ID trigger);
  
public:
  virtual bool Init(const SharedRef<Activity>& activity, LPDIRECTINPUT8 input) override;
  virtual bool Uninit(LPDIRECTINPUT8 input) override;
  virtual void InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state) override;
  virtual void ApplyProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state) override;

private:
  T_UINT8 user_index_;
  const XInputInput* inputs_;
  T_UINT8 inputs_count_;
  EngineInput::Analog::ID left_;
  EngineInput::Analog::ID right_;
  EngineInput::Analog::ID trigger_;

  XINPUT_STATE xstate_;
};
