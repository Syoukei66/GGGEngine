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
    for (typename std::list<T*>::iterator it = this->begin(); it != this->end(); ++it)
    {
      T* device = (*it);
      this->OnUnloadDevice(device);
    }
    this->devices_.clear();
    return true;
  }
  virtual bool OnLoadDevice(T* device) = 0;
  virtual bool OnUnloadDevice(T* device) = 0;

  void InputProcess(EngineInputState* state)
  {
    //for (typename std::list<T*>::iterator it = this->begin(); it != this->end(); ++it)
    //{
    //  T* device = (*it);   
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
    return true;
  }

public:
  inline typename std::list<T*>::iterator begin()
  {
    return this->devices_.begin();
  }
  inline typename std::list<T*>::iterator end()
  {
    return this->devices_.end();
  }
private:
  typename std::list<T*> devices_;
};
