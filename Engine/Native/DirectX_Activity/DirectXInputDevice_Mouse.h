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
  DirectXInputDevice_Mouse(
    T_UINT8 handler, const MouseInput* mouse_inputs, T_UINT8 mouse_inputs_count,
    EngineInput::Analog::ID move_input_id, EngineInput::Analog::ID screen_input_id,
    bool bind = false);

public:
  virtual bool Init(LPDIRECTINPUT8 input) override;
  virtual bool Uninit(LPDIRECTINPUT8 input) override;
  virtual void InputProcess(T_UINT8 handler, EngineInputState* state) override;

private:
  const MouseInput* mouse_inputs_;
  T_UINT8 mouse_inputs_count_;
  EngineInput::Analog::ID move_input_id_;
  EngineInput::Analog::ID position_input_id_;
  bool bind_;
};