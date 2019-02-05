#include "DirectInputDevice_Keyboard.h"
#include <Native/Windows/WindowsApplication.h>

DirectInputDevice_KeyBoard::DirectInputDevice_KeyBoard(T_UINT8 handler, const KeyboardInput* inputs, T_UINT8 inputs_count)
  : DirectInputDevice(handler)
  , inputs_(inputs)
  , inputs_count_(inputs_count)
{}

bool DirectInputDevice_KeyBoard::Init(const SharedRef<Activity>& activity, LPDIRECTINPUT8 input)
{
  //DirectInputDeviceの初期化
  if (FAILED(input->CreateDevice(
    GUID_SysKeyboard,
    &this->device_,
    NULL
  )))
  {
    return false;
  }

  //デバイスをキーボードに設定
  if (FAILED(this->device_->SetDataFormat(&c_dfDIKeyboard)))
  {
    return false;
  }

  HWND hwnd = WindowsApplication::GetMainActivityContext().GetWindowHandle();

  //協調レベルの設定
  if (FAILED(this->device_->SetCooperativeLevel(hwnd,
    DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
  {
    return false;
  }

  //デバイスを取得する
  this->device_->Acquire();

  return true;
}

bool DirectInputDevice_KeyBoard::Uninit(LPDIRECTINPUT8 input)
{
  if (this->device_)
  {
    this->device_->Release();
    this->device_ = NULL;
  }
  return true;
}


void DirectInputDevice_KeyBoard::InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state)
{
  BYTE diks[256];
  if (FAILED(this->device_->GetDeviceState(sizeof(diks), &diks)))
  {
    this->device_->Acquire();
    return;
  }
  for (int i = 0; i < this->inputs_count_; ++i)
  {
    state->PreInputDigital(handler, this->inputs_[i].id);
    if (diks[this->inputs_[i].input] & 0x80)
    {
      state->InputDigital(handler, this->inputs_[i].id);
    }
    state->PostInputDigital(handler, this->inputs_[i].id);
  }
}
