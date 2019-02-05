#pragma once

#include "DirectInputDevice.h"

class DirectInputDevice_KeyBoard : public DirectInputDevice
{
public:
  struct KeyboardInput
  {
    EngineInput::Digital::ID id;
    DWORD input;
  };

public:
  DirectInputDevice_KeyBoard(T_UINT8 handler, const KeyboardInput* inputs, T_UINT8 inputs_count);

public:
  virtual bool Init(const SharedRef<Activity>& activity, LPDIRECTINPUT8 input) override;
  virtual bool Uninit(LPDIRECTINPUT8 input) override;
  virtual void InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state) override;

private:
  const KeyboardInput* inputs_;
  T_UINT8 inputs_count_;
};
