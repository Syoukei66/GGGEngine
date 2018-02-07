#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <InputDevice.h>
#include <EngineInputEvent.h>

class DirectXInputDevice : public InputDevice
{
public:
  DirectXInputDevice(T_UINT8 handler)
    : InputDevice(handler)
  {}
  virtual ~DirectXInputDevice() {}

public:
  virtual bool Init(LPDIRECTINPUT8 input) = 0;
  virtual bool Uninit(LPDIRECTINPUT8 input) = 0;

protected:
  LPDIRECTINPUTDEVICE8 device_;
};