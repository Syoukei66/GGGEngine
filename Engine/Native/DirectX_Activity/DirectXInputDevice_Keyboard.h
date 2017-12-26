#pragma once

#include "DirectXInputDevice.h"
#include <EngineInput.h>

class DirectXInputDevice_KeyBoard : public DirectXInputDevice
{
public:
  struct KeyboardInput
  {
    EngineInput::Digital::ID id;
    DWORD input;
  };

public:
  DirectXInputDevice_KeyBoard(T_UINT8 handler, const KeyboardInput* inputs, T_UINT8 inputs_count);

public:
  virtual bool Init(LPDIRECTINPUT8 input) override;
  virtual bool Uninit(LPDIRECTINPUT8 input) override;
  virtual void InputProcess(T_UINT8 handler, EngineInputState* state) override;

private:
  const KeyboardInput* inputs_;
  T_UINT8 inputs_count_;
};
