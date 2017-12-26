#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <list>
#include <EngineInputEvent.h>
#include <InputDeviceManager.h>
#include "DirectXInputDevice.h"

class DirectXInputDeviceManager : public InputDeviceManager<DirectXInputDevice>
{
public:
  DirectXInputDeviceManager();
  ~DirectXInputDeviceManager();

  virtual bool OnLoadDevice(DirectXInputDevice* device) override;
  virtual bool OnUnloadDevice(DirectXInputDevice* device) override;

private:
  LPDIRECTINPUT8 dinput_;

};