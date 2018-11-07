#include "DirectInputDeviceManager.h"

DirectInputDeviceManager::DirectInputDeviceManager()
{  
  //DirectInput‚Ì‰Šú‰»
  DirectInput8Create(
    GetModuleHandle(NULL),
    DIRECTINPUT_VERSION,
    IID_IDirectInput8,
    (void**)&this->dinput_,
    NULL
  );
}

DirectInputDeviceManager::~DirectInputDeviceManager()
{
  if (this->dinput_)
  {
    this->dinput_->Release();
  }
}

bool DirectInputDeviceManager::OnLoadDevice(DirectInputDevice* device)
{
  return device->Init(this->dinput_);
}

bool DirectInputDeviceManager::OnUnloadDevice(DirectInputDevice* device)
{
  return device->Uninit(this->dinput_);
}
