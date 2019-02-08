#pragma once

#include <Core/Application/Input/EngineInputState.h>
#include "InputDevice.h"

template<class T>
class InputDeviceManager
{
public:
  virtual bool UnloadAllDevices()
  {
    for (const auto& pair : this->devices_map_)
    {
      for (T* device : pair.second)
      {
        this->OnUnloadDevice(device);
        delete device;
      }
    }
    return true;
  }

  virtual bool UnloadDevices(const SharedRef<Activity>& activity)
  {
    std::vector<T*>* devices = &this->devices_map_.at(activity->GetContext().GetActivityID());
    for (T* device : *devices)
    {
      this->OnUnloadDevice(device);
      delete device;
    }
    devices->clear();
    return true;
  }
  virtual bool OnLoadDevice(const SharedRef<Activity>& activity, T* device) = 0;
  virtual bool OnUnloadDevice(T* device) = 0;

  void InputProcess(const SharedRef<Activity>& activity, EngineInputState* state)
  {
    const std::vector<T*> devices = this->devices_map_.at(activity->GetContext().GetActivityID());
    for (T* device : devices)
    {
      device->InputProcess(device->GetHandler(), activity, state);
    }
  }

  void ApplyProcess(const SharedRef<Activity>& activity, EngineInputState* state)
  {
    const std::vector<T*> devices = this->devices_map_.at(activity->GetContext().GetActivityID());
    for (T* device : devices)
    {
      device->ApplyProcess(device->GetHandler(), activity, state);
    }
  }

public:
  GG_INLINE bool LoadDevice(const SharedRef<Activity>& activity, T* device)
  {
    if (!this->OnLoadDevice(activity, device))
    {
      return false;
    }
    this->devices_map_[activity->GetContext().GetActivityID()].emplace_back(device);
    return true;
  }

private:
  typename std::unordered_map<T_UINT64, std::vector<T*>> devices_map_;
};
