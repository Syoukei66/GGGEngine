#pragma once

#include <list>
#include "EngineInputEvent.h"
#include "InputDevice.h"

template<class T>
class InputDeviceManager
{
public:
  virtual bool UnloadDevices()
  {
    for (T* device : this->devices_)
    {
      this->OnUnloadDevice(device);
      delete device;
    }
    this->devices_.clear();
    return true;
  }
  virtual bool OnLoadDevice(T* device) = 0;
  virtual bool OnUnloadDevice(T* device) = 0;

  void InputProcess(EngineInputState* state)
  {
    for (T* device : this->devices_)
    {
      device->InputProcess(device->GetHandler(), state);
    }
  }

public:
  inline bool LoadDevice(T* device)
  {
    if (!this->OnLoadDevice(device))
    {
      return false;
    }
    this->devices_.push_back(device);
    return true;
  }
  inline bool UnloadDevice(T* device)
  {
    if (!this->OnUnloadDevice(device))
    {
      return false;
    }
    this->devices_.remove(device);
    delete device;
    return true;
  }

private:
  typename std::list<T*> devices_;
};
