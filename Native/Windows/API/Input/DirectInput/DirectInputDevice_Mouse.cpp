#include "DirectInputDevice_Mouse.h"

#include <Native/Windows/WindowsApplication.h>

DirectInputDevice_Mouse::DirectInputDevice_Mouse(
  T_UINT8 handler,
  const MouseInput* mouse_inputs,
  T_UINT8 mouse_inputs_count,
  EngineInput::Analog::ID move_input_id,
  EngineInput::Analog::ID screen_input_id,
  EngineInput::Analog::ID wheel_input_id,
  bool bind
)
  : DirectInputDevice(handler)
  , mouse_inputs_(mouse_inputs)
  , mouse_inputs_count_(mouse_inputs_count)
  , move_input_id_(move_input_id)
  , position_input_id_(screen_input_id)
  , wheel_input_id_(wheel_input_id)
  , bind_(bind)
  , mouse_state_()
{}

bool DirectInputDevice_Mouse::Init(const SharedRef<Activity>& activity, LPDIRECTINPUT8 input)
{
  //DirectInputDevice�̏�����
  if (FAILED(input->CreateDevice(
    GUID_SysMouse,
    &this->device_,
    NULL
  )))
  {
    return false;
  }

  //�f�o�C�X���}�E�X�ɐݒ�
  if (FAILED(this->device_->SetDataFormat(&c_dfDIMouse2)))
  {
    return false;
  }

  HWND hwnd = (HWND)activity->GetContext().GetActivityID();

  //�������x���̐ݒ�
  if (FAILED(this->device_->SetCooperativeLevel(hwnd,
    DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
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

  //�f�o�C�X���擾����
  this->device_->Acquire();

  if (this->bind_)
  {
    // �}�E�X�ړ��͈͂̐ݒ�
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

bool DirectInputDevice_Mouse::Uninit(LPDIRECTINPUT8 input)
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

void DirectInputDevice_Mouse::InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state)
{
  if (FAILED(this->device_->GetDeviceState(sizeof(this->mouse_state_), &this->mouse_state_)))
  {
    this->device_->Acquire();
    return;
  }
}

void DirectInputDevice_Mouse::ApplyProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState * state)
{
  const ActivityContext& context = activity->GetContext();
  // �}�E�X�{�^���̓���
  for (int i = 0; i < this->mouse_inputs_count_; ++i)
  {
    state->PreInputDigital(handler, this->mouse_inputs_[i].id);
    if (this->mouse_state_.rgbButtons[this->mouse_inputs_[i].input] & 0x80)
    {
      state->InputDigital(handler, this->mouse_inputs_[i].id);
    }
    state->PostInputDigital(handler, this->mouse_inputs_[i].id);
  }

  // �}�E�X����̓���
  const T_FLOAT w = context.GetScreenWidth();
  const T_FLOAT h = context.GetScreenHeight();

  state->PreInputAnalog(handler, this->move_input_id_);
  state->InputAnalog(handler, this->move_input_id_, 0, this->mouse_state_.lX * 0.1f);
  state->InputAnalog(handler, this->move_input_id_, 1, this->mouse_state_.lY * 0.1f);
  state->PostInputAnalog(handler, this->move_input_id_);

  // �}�E�X���W�̓���
  state->PreInputAnalog(handler, this->position_input_id_);
  POINT pos;
  if (GetCursorPos(&pos))
  {
    HWND hwnd = (HWND)context.GetActivityID();
    RECT rc;
    GetWindowRect(hwnd, &rc);

    RECT client;
    GetClientRect(hwnd, &client);
    T_FLOAT edge = ((rc.right - rc.left) - (client.right - client.left)) * 0.5f;
    pos.x -= (LONG)(rc.left + edge);
    pos.y -= (LONG)(rc.top + ((rc.bottom - rc.top) - (client.bottom - client.top)) - edge);

    state->InputAnalog(handler, this->position_input_id_, 0, (pos.x / w - 0.5f) * 2.0f);
    state->InputAnalog(handler, this->position_input_id_, 1, (pos.y / h - 0.5f) * 2.0f);
  }

  //const T_FLOAT pre_x = state->GetAnalogInput(handler)->GetOldValue(this->position_input_id_, 0);
  //const T_FLOAT pre_y = state->GetAnalogInput(handler)->GetOldValue(this->position_input_id_, 1);
  //state->InputAnalog(handler, this->position_input_id_, 0, pre_x + (mouse_state.lX / w));
  //state->InputAnalog(handler, this->position_input_id_, 1, pre_y - (mouse_state.lY / h));

  state->PostInputAnalog(handler, this->position_input_id_);

  // �}�E�X�z�C�[���̓���
  state->PreInputAnalog(handler, this->wheel_input_id_);
  state->InputAnalog(handler, this->wheel_input_id_, 0, this->mouse_state_.lZ * 0.1f);
  state->PostInputAnalog(handler, this->wheel_input_id_);
  state->PostInputAnalog(handler, this->wheel_input_id_);
}
