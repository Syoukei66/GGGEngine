#include "DirectXInputDeviceManager.h"

DirectXInputDeviceManager::DirectXInputDeviceManager()
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

DirectXInputDeviceManager::~DirectXInputDeviceManager()
{
  if (this->dinput_)
  {
    this->dinput_->Release();
  }
}

bool DirectXInputDeviceManager::OnLoadDevice(DirectXInputDevice* device)
{
  return device->Init(this->dinput_);
}

bool DirectXInputDeviceManager::OnUnloadDevice(DirectXInputDevice* device)
{
  return device->Uninit(this->dinput_);
}
