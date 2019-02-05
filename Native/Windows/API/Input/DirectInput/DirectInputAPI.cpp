#include "DirectInputAPI.h"
#include <Native/Windows/API/Input/DirectInput/DirectInputDeviceManager.h>
#include <Native/Windows/API/Input/DirectInput/DirectInputImplements.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(DirectInputAPI)
{
  this->input_ = new DirectInputDeviceManager();
  this->native_implements_->SetupInputDevices(Application::GetMainActivity(), this->input_);

  return true;
}

GG_DESTRUCT_FUNC_IMPL(DirectInputAPI)
{
  if (this->input_)
  {
    this->input_->UnloadAllDevices();
    delete this->input_;
    this->input_ = nullptr;
  }
  delete this->native_implements_;

  return true;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void DirectInputAPI::InputProcess(const SharedRef<Activity>& activity, EngineInputState* state)
{
  this->input_->InputProcess(activity, state);
}

void DirectInputAPI::CreateSubActivityResources(const SharedRef<Activity>& activity)
{
  this->native_implements_->SetupInputDevices(activity, this->input_);

}
