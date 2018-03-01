#include "DirectXInputDevice_Mouse.h"
#include <Director.h>

#include "DirectXDirector.h"

DirectXInputDevice_Mouse::DirectXInputDevice_Mouse(T_UINT8 handler, const MouseInput* mouse_inputs, T_UINT8 mouse_inputs_count, EngineInput::Analog::ID move_input_id, EngineInput::Analog::ID screen_input_id, bool bind)
  : DirectXInputDevice(handler)
  , mouse_inputs_(mouse_inputs)
  , mouse_inputs_count_(mouse_inputs_count)
  , move_input_id_(move_input_id)
  , position_input_id_(position_input_id_)
  , bind_(bind)
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

  if (this->bind_)
  {
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

    ShowCursor(false);
  }

  return true;
}

bool DirectXInputDevice_Mouse::Uninit(LPDIRECTINPUT8 input)
{
  if (this->bind_)
  {
    ClipCursor(NULL);
    ShowCursor(true);
  }
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
    state->PreInputDigital(handler, this->mouse_inputs_[i].id);
    if (mouse_state.rgbButtons[this->mouse_inputs_[i].input] & 0x80)
    {
      state->InputDigital(handler, this->mouse_inputs_[i].id);
    }
    state->PostInputDigital(handler, this->mouse_inputs_[i].id);
  }
  const T_FLOAT w = (T_FLOAT)Director::GetInstance()->GetScreenWidth();
  const T_FLOAT h = (T_FLOAT)Director::GetInstance()->GetScreenHeight();

  state->PreInputAnalog(handler, this->move_input_id_);
  state->InputAnalog(handler, this->move_input_id_, 0, mouse_state.lX * 0.1f);
  state->InputAnalog(handler, this->move_input_id_, 1, mouse_state.lY * 0.1f);
  state->PostInputAnalog(handler, this->move_input_id_);

  state->PreInputAnalog(handler, this->position_input_id_);
  const T_FLOAT pre_x = state->GetAnalogInput(handler)->GetOldValue(this->position_input_id_, 0);
  const T_FLOAT pre_y = state->GetAnalogInput(handler)->GetOldValue(this->position_input_id_, 1);
  state->InputAnalog(handler, this->position_input_id_, 0, pre_x + (mouse_state.lX / w - 0.5f));
  state->InputAnalog(handler, this->position_input_id_, 1, pre_y - (mouse_state.lY / h - 0.5f));
  state->PostInputAnalog(handler, this->position_input_id_);
}
