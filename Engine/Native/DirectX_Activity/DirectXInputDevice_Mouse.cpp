#include "DirectXInputDevice_Mouse.h"
#include <Director.h>

#include "DirectXDirector.h"

DirectXInputDevice_Mouse::DirectXInputDevice_Mouse(T_UINT8 handler, const MouseInput* mouse_inputs, T_UINT8 mouse_inputs_count, EngineInput::Analog::ID analog_input_id)
  : DirectXInputDevice(handler)
  , mouse_inputs_(mouse_inputs)
  , mouse_inputs_count_(mouse_inputs_count)
  , analog_input_id_(analog_input_id)
{}

bool DirectXInputDevice_Mouse::Init(LPDIRECTINPUT8 input)
{
  //DirectInputDeviceの初期化
  if (FAILED(input->CreateDevice(
    GUID_SysMouse,
    &this->device_,
    NULL
  )))
  {
    return false;
  }

  //デバイスをマウスに設定
  if (FAILED(this->device_->SetDataFormat(&c_dfDIMouse2)))
  {
    return false;
  }

  HWND hwnd = DirectXDirector::GetInstance().GetHWnd();

  //協調レベルの設定
  if (FAILED(this->device_->SetCooperativeLevel(hwnd,
    DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
  {
    return false;
  }

  DIPROPDWORD diprop;
  diprop.diph.dwSize = sizeof(diprop);
  diprop.diph.dwHeaderSize = sizeof(diprop.diph);
  diprop.diph.dwObj = 0;
  diprop.diph.dwHow = DIPH_DEVICE;
  diprop.dwData = DIPROPAXISMODE_REL;
  this->device_->SetProperty(DIPROP_AXISMODE, &diprop.diph);

  //デバイスを取得する
  this->device_->Acquire();

  ShowCursor(false);
  
  // マウス移動範囲の設定
  RECT rc;
  GetWindowRect(hwnd, &rc);

  //RECT client; 
  //GetClientRect(hwnd, &client);

  //T_FLOAT client_w = client.right - client.left;
  //T_FLOAT client_h = client.bottom - client.top;

  //POINT point;
  //point.x = client.left;
  //point.y = client.top;
  //ClientToScreen(hwnd, &point);

  //rc.left = point.x + client_w * 0.25f;
  //rc.right = rc.left + client_w * 0.5f;
  //rc.top = point.y + client_h * 0.25f;
  //rc.bottom = rc.top + client_h * 0.5f;

  T_FLOAT rc_w = (T_FLOAT)rc.right - (T_FLOAT)rc.left;
  T_FLOAT rc_h = (T_FLOAT)rc.bottom - (T_FLOAT)rc.top;
  rc.left += (LONG)(rc_w * 0.5f);
  rc.right = rc.left;
  rc.top += (LONG)(rc_h * 0.5f);
  rc.bottom = rc.top;
  ClipCursor(&rc);

  // マウス移動範囲の解除

  return true;
}

bool DirectXInputDevice_Mouse::Uninit(LPDIRECTINPUT8 input)
{
  ClipCursor(NULL);
  ShowCursor(true);
  if (this->device_)
  {
    this->device_->Release();
    this->device_ = NULL;
  }
  return true;
}

void DirectXInputDevice_Mouse::InputProcess(T_UINT8 handler, EngineInputState* state)
{
  DIMOUSESTATE2 mouse_state;
  if (FAILED(this->device_->GetDeviceState(sizeof(mouse_state), &mouse_state)))
  {
    this->device_->Acquire();
    return;
  }
  for (int i = 0; i < this->mouse_inputs_count_; ++i)
  {
    if (mouse_state.rgbButtons[this->mouse_inputs_[i].input] & 0x80)
    {
      state->PreInputDigital(handler, this->mouse_inputs_[i].id);
      state->InputDigital(handler, this->mouse_inputs_[i].id);
      state->PostInputDigital(handler, this->mouse_inputs_[i].id);
    }
  }
  const T_FLOAT w = (T_FLOAT)Director::GetInstance()->GetScreenWidth();
  const T_FLOAT h = (T_FLOAT)Director::GetInstance()->GetScreenHeight();
  state->PreInputAnalog(handler, this->analog_input_id_);
  const T_FLOAT pre_x = state->GetAnalogInput(handler)->GetOldValue(this->analog_input_id_, 0);
  const T_FLOAT pre_y = state->GetAnalogInput(handler)->GetOldValue(this->analog_input_id_, 1);
  state->InputAnalog(handler, this->analog_input_id_, 0, pre_x + mouse_state.lX / w);
  state->InputAnalog(handler, this->analog_input_id_, 1, pre_y - mouse_state.lY / h);
  state->PostInputAnalog(handler, this->analog_input_id_);
}
