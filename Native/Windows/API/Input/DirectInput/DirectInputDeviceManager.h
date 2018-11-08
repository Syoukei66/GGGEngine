#pragma once

#include <Core/Application/Input/InputDeviceManager.h>
#include "DirectInputDevice.h"

class DirectInputDeviceManager : public InputDeviceManager<DirectInputDevice>
{
public:
  DirectInputDeviceManager();
  ~DirectInputDeviceManager();

  virtual bool OnLoadDevice(DirectInputDevice* device) override;
  virtual bool OnUnloadDevice(DirectInputDevice* device) override;

private:
  LPDIRECTINPUT8 dinput_;

};