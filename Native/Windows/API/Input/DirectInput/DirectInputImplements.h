#pragma once

#include "DirectInputDeviceManager.h"

class DirectInputImplements
{
public:
  void SetupInputDevices(const SharedRef<Activity>& activity, DirectInputDeviceManager* manager);
};