#pragma once

#include <Core/Application/Input/InputDevice.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")

class DirectInputDevice : public InputDevice
{
public:
  DirectInputDevice(T_UINT8 handler)
    : InputDevice(handler)
  {}
  virtual ~DirectInputDevice() {}

public:
  virtual bool Init(const SharedRef<Activity>& activity, LPDIRECTINPUT8 input) = 0;
  virtual bool Uninit(LPDIRECTINPUT8 input) = 0;

protected:
  LPDIRECTINPUTDEVICE8 device_;
};