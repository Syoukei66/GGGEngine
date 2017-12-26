#pragma once

#include "DirectXInputDevice.h"

class DirectXInputDevice_Mouse : public DirectXInputDevice
{
public:
  enum MouseRgbButtonKind {
    MOUSE_RGB_BUTTON_LEFT,
    MOUSE_RGB_BUTTON_RIGHT,
    MOUSE_RGB_BUTTON_CENTER,

    MOUSE_RGB_BUTTON_DATANUM,
  };

  struct MouseInput
  {
    EngineInput::Digital::ID id;
    MouseRgbButtonKind input;
  };

public:
  DirectXInputDevice_Mouse(T_UINT8 handler, const MouseInput* mouse_inputs, T_UINT8 mouse_inputs_count, EngineInput::Analog::ID analog_input_id);

public:
  virtual bool Init(LPDIRECTINPUT8 input) override;
  virtual bool Uninit(LPDIRECTINPUT8 input) override;
  virtual void InputProcess(T_UINT8 handler, EngineInputState* state) override;

private:
  const MouseInput* mouse_inputs_;
  T_UINT8 mouse_inputs_count_;
  EngineInput::Analog::ID analog_input_id_;
};