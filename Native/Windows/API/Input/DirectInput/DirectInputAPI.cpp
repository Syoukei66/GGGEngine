#include "DirectInputAPI.h"
#include <Native/Windows/API/Input/DirectInput/DirectInputDeviceManager.h>
#include <Native/Windows/API/Input/DirectInput/DirectInputImplements.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(DirectInputAPI, const InputSetting& setting)
{
  InputAPI::Init(setting);
  this->input_ = new DirectInputDeviceManager();
  this->native_implements_->SetupInputDevices(this->input_);

  return true;
}

GG_DESTRUCT_FUNC_IMPL(DirectInputAPI)
{
  if (this->input_)
  {
    this->input_->UnloadDevices();
    delete this->input_;
    this->input_ = nullptr;
  }
  delete this->native_implements_;

  return true;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void DirectInputAPI::InputProcess(EngineInputState* state)
{
  this->input_->InputProcess(state);
}
